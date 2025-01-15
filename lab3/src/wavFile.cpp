#include "wavFile.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include "exceptions.h"

struct WavHeader {
    union {
        char groupID[4];
        uint32_t groupIDi;
    };
    int32_t size;
    union {
        char riffType[4];
        uint32_t riffTypei;
    };
};

struct WavChunkBase {
    union {
        char chunkID[4];
        uint32_t chunkIDi;
    };
    int32_t chunkSize;
};

struct WavFormat : WavChunkBase {
    int16_t wFormatTag;
    uint16_t wChannels;
    uint32_t dwSamplesPerSec;
    uint32_t dwAvgBytesPerSec;
    uint16_t wBlockAlign;
    uint16_t wBitsPerSample;
};

WavFile::WavFile(std::string filename)
    : filename(std::move(filename)), sampleRate(defaultSampleRate) {}

void WavFile::read() {
    std::ifstream file(this->filename, std::ios::binary);
    if (!file) {
        throw FileIOException("Could not open file: " +
            std::string(std::filesystem::absolute(filename)));
    }

    parseHeader(file);

    WavChunkBase chunk = {};

    // Skip all chunks except "data"
    while (true) {
        file.read(reinterpret_cast<char *>(&chunk), sizeof(chunk));
        if (!file) {
            throw FileIOException(
                "Error reading WAV chunk from file: " +
                std::string(std::filesystem::absolute(filename)));
        }

        // "data" = 0x61746164
        if (chunk.chunkIDi == 0x61746164) break;

        // Skip the chunk data
        file.seekg(chunk.chunkSize, std::ios::cur);
    }

    if (chunk.chunkSize % sizeof(int16_t) != 0) {
        throw UnsupportedFormatException();
    }

    // Reading samples as 16-bit signed integers
    samples.resize(chunk.chunkSize / sizeof(int16_t));
    file.read(reinterpret_cast<char *>(samples.data()), chunk.chunkSize);
    if (!file) {
        throw FileIOException(
            "Error reading WAV data from file: " +
            std::string(std::filesystem::absolute(filename)));
    }
}

void WavFile::parseHeader(std::ifstream &file) {
    WavHeader header = {};
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (!file) {
        throw FileIOException(
            "Error reading WAV header from file: " +
            std::string(std::filesystem::absolute(filename)));
    }

    // Validate header
    // "RIFF" = 0x46464952, "WAVE" = 0x45564157
    if (header.groupIDi != 0x46464952 || header.riffTypei != 0x45564157) {
        throw UnsupportedFormatException();
    }

    WavFormat format = {};
    file.read(reinterpret_cast<char *>(&format), sizeof(format));
    if (!file) {
        throw FileIOException(
            "Error reading WAV format from file: " +
            std::string(std::filesystem::absolute(filename)));
    }

    // Validate format
    // "fmt " = 0x20746d66
    if (format.chunkIDi != 0x20746d66 || format.wFormatTag != 1 ||
        format.wChannels != 1 || format.dwSamplesPerSec != defaultSampleRate ||
        format.wBitsPerSample != 16) {
        throw UnsupportedFormatException();
    }

    sampleRate = format.dwSamplesPerSec;
}

void WavFile::write(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw FileIOException("Could not create file: " +
            std::string(std::filesystem::absolute(filename)));
    }

    uint32_t dataSize = samples.size() * sizeof(int16_t);

    WavFormat format = {};
    format.chunkIDi = 0x20746d66;
    format.chunkSize = 16;
    format.wFormatTag = 1;
    format.wChannels = 1;
    format.dwSamplesPerSec = sampleRate * format.wChannels;
    format.dwAvgBytesPerSec = sampleRate * format.wChannels * sizeof(int16_t);
    format.wBlockAlign = format.wChannels * sizeof(int16_t);
    format.wBitsPerSample = sizeof(int16_t) * 8;

    WavChunkBase dataBase = {};
    dataBase.chunkIDi = 0x61746164;
    dataBase.chunkSize = dataSize;

    WavHeader header = {};
    header.groupIDi = 0x46464952;
    header.size = sizeof(header.riffType) +
        sizeof(WavFormat) + sizeof(WavChunkBase) + dataSize;
    header.riffTypei = 0x45564157;

    file.write(reinterpret_cast<char *>(&header), sizeof(header));
    file.write(reinterpret_cast<char *>(&format), sizeof(format));
    file.write(reinterpret_cast<char *>(&dataBase), sizeof(dataBase));
    file.write(reinterpret_cast<char *>(samples.data()), dataSize);
}
