#ifndef LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
#define LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_

#include <set>
#include <string>
#include "Reader.h"
#include "Writer.h"

class FrequencyParser {
 public:
    FrequencyParser(const Reader* input_reader, const CSVWriter* output_writer);
    void parseAndWrite();

 private:
    Reader reader;
    CSVWriter writer;

    std::multiset<std::string> wordSet;
};

#endif  // LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
