#include "../include/Reader.h"

#include <iostream>
#include <fstream>
#include <filesystem>

int Reader::readTXT(const std::string& inputFile) {
    std::ifstream fileIn(inputFile);
    if (!fileIn.is_open()) {
        std::cerr << "Error opening input file: "
        << std::filesystem::absolute(inputFile).string() << std::endl;
        return 1;
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
    return 0;
}

std::map<std::string, int> Reader::getWordMap() const {
    return wordFrequencyMap;
}
