#include "FrequencyParser.h"

#include <algorithm>
#include <filesystem>
#include <vector>
#include <string>
#include "Reader.h"
#include "Writer.h"

FrequencyParser::FrequencyParser(
    const Reader* input_reader, const CSVWriter* output_writer):
    reader(*input_reader), writer(*output_writer) {}

void FrequencyParser::parseAndWrite() {
    reader.readTXT();
    const auto wordFrequencyMap = reader.getWordMap();

    for (const auto& [fst, snd] : wordFrequencyMap) {
        for (int i = 0; i < snd; ++i) {
            wordSet.emplace(fst);
        }
    }

    std::vector<std::pair<std::string, int>> sortedList;
    for (const auto& word : wordSet) {
        if (sortedList.empty() || sortedList.back().first != word) {
            sortedList.emplace_back(word, wordSet.count(word));
        }
    }

    std::sort(sortedList.begin(), sortedList.end(),
        [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    writer.writeCSV(sortedList, wordSet.size());
}
