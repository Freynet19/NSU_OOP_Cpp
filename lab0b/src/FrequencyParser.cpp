#include "FrequencyParser.h"

#include <algorithm>
#include "Reader.h"
#include "Writer.h"

FrequencyParser::FrequencyParser(
    const Reader* input_reader, const CSVWriter* output_writer):
    reader(*input_reader), writer(*output_writer) {}

void FrequencyParser::parseAndWrite() {

    reader.readTXT();
    const auto wordFrequencyMap = reader.getWordMap();

    for (const auto& pair : wordFrequencyMap) {
        sortedList.emplace_back(pair.first, pair.second);
        wordsCount += pair.second;
    }

    auto comp = [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    };
    std::sort(sortedList.begin(), sortedList.end(), comp);

    writer.writeCSV(sortedList, wordsCount);
}
