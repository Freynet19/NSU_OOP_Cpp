#include "../include/Parser.h"

#include <fstream>
#include <algorithm>
#include "../include/Reader.h"
#include "../include/Writer.h"

int Parser::parseCSV(const std::string& inputFile,
                     const std::string& outputFile) {
    Reader reader;
    if (reader.readTXT(inputFile) != 0) return 1;

    const auto wordFrequencyMap = reader.getWordMap();

    for (const auto& pair : wordFrequencyMap) {
        sortedList.emplace_back(pair.first, pair.second);
        wordsCount += pair.second;
    }

    auto comp = [](const auto& a, const auto& b) {
        return b.second < a.second;
    };
    std::sort(sortedList.begin(), sortedList.end(), comp);

    if (Writer::writeCSV(outputFile, sortedList, wordsCount) != 0) return 1;

    return 0;
}
