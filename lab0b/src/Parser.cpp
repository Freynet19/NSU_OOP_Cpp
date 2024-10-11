#include "../include/Parser.h"

#include <fstream>
#include <algorithm>

void Parser::parseForCSV(std::map<std::string, int> const& wordFrequencyMap) {
    for (const auto& pair : wordFrequencyMap) {
        sortedList.emplace_back(pair.first, pair.second);
        wordsCount += pair.second;
    }

    auto comp = [](const auto& a, const auto& b) {
        return b.second < a.second;
    };
    std::sort(sortedList.begin(), sortedList.end(), comp);
}

wordList Parser::getWordList() const {
    return sortedList;
}

int Parser::getWordsCount() const {
    return wordsCount;
}
