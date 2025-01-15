#ifndef LAB3_SRC_INCLUDE_WAVFILE_H_
#define LAB3_SRC_INCLUDE_WAVFILE_H_

#include <cstdint>
#include <string>
#include <vector>

class WavFile {
 public:
    explicit WavFile(std::string filename);
    void read();
    void write(const std::string &filename);
    const std::vector<int16_t> &getSamples() { return samples; }
    void setSamples(std::vector<int16_t> &&samples) { this->samples = samples; }

    static constexpr uint32_t defaultSampleRate = 44100;

 private:
    std::string filename;
    std::vector<int16_t> samples;
    uint32_t sampleRate;
    void parseHeader(std::ifstream &file);
};

#endif  // LAB3_SRC_INCLUDE_WAVFILE_H_
