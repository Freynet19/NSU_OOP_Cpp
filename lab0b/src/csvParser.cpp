#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/csvParser.h"

int CsvParser::scanTXT(const std::string& inputFile) {
    std::ifstream fileIn(inputFile);
    if (!fileIn.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
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

int CsvParser::generateCSV(const std::string& outputFile) {
    std::ofstream fileOut(outputFile);
    if (!fileOut.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, int>> sortedWordList;
    int wordsCount = 0;
    for (const auto& pair : wordFrequencyMap) {
        sortedWordList.emplace_back(pair.first, pair.second);
        wordsCount += pair.second;
    }

    auto comp = [](const auto& a, const auto& b) {
        return b.second < a.second;
    };
    std::sort(sortedWordList.begin(), sortedWordList.end(), comp);

    fileOut << "Word,Frequency,Frequency(%)" << std::endl;
    for (const auto& pair : sortedWordList) {
        fileOut << pair.first << ","
                << pair.second << ","
                << pair.second * 100.0 / wordsCount << std::endl;
    }

    fileOut.close();
    return 0;
}
