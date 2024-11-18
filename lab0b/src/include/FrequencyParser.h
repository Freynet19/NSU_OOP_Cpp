#ifndef LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
#define LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_

#include <string>
#include <vector>
#include <utility>
#include "Reader.h"
#include "Writer.h"

class FrequencyParser {
 public:
    FrequencyParser(const Reader* input_reader, const CSVWriter* output_writer);
    void parseAndWrite();
    static void validateArgs(int argc, char* argv[]);

 private:
    Reader reader;
    CSVWriter writer;
    std::vector<std::pair<std::string, int>> sortedList; // multiset
    int wordsCount = 0;
};

#endif  // LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
