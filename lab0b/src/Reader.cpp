#include "Reader.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>

Reader::Reader(const char* inputTXT): inputFile(inputTXT) {}

void Reader::readTXT() {
    std::ifstream fileIn(inputFile);
    if (!fileIn.is_open()) {
        throw std::runtime_error("Error opening input file: " +
            std::filesystem::absolute(inputFile).string());
    }

    std::string line;
    while (std::getline(fileIn, line)) {
        for (char& c : line) {
            if (!std::isalnum(c)) c = ' ';
        }
        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            std::transform(word.begin(), word.end(),
                word.begin(), tolower);
            ++wordFrequencyMap[word];
        }
    }

    fileIn.close();
}

std::map<std::string, int> Reader::getWordMap() const {
    return wordFrequencyMap;
}
