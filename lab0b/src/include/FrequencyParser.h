#ifndef LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
#define LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_

#include <string>
#include <vector>
#include <utility>

class FrequencyParser {
 public:
    FrequencyParser(const std::string& inputTXT, const std::string& outputCSV);
    int GetWordFrequency();

 private:
    std::string inputFile;
    std::string outputFile;
    std::vector<std::pair<std::string, int>> sortedList;
    int wordsCount = 0;
};

#endif  // LAB0B_SRC_INCLUDE_FREQUENCYPARSER_H_
