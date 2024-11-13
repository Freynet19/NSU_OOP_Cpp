#include "Reader.h"

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
        std::string word;
        for (char i : line) {
            if (std::isalnum(i)) {
                word.push_back(std::tolower(i));
            } else if (!word.empty()) {
                ++wordFrequencyMap[word];
                word.clear();
            }
        }
        if (!word.empty()) ++wordFrequencyMap[word];
    }

    fileIn.close();
}

std::map<std::string, int> Reader::getWordMap() const {
    return wordFrequencyMap;
}
