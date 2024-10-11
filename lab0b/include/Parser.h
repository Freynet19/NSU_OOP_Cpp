#ifndef LAB0B_INCLUDE_PARSER_H_
#define LAB0B_INCLUDE_PARSER_H_

#include <string>
#include <vector>
#include <utility>

class Parser {
 public:
    int parseCSV(const std::string& inputFile, const std::string& outputFile);

 private:
    std::vector<std::pair<std::string, int>> sortedList;
    int wordsCount = 0;
};

#endif  // LAB0B_INCLUDE_PARSER_H_
