#ifndef LAB0B_INCLUDE_CSVPARSER_H_
#define LAB0B_INCLUDE_CSVPARSER_H_

#include <map>
#include <string>

class CsvParser {
 public:
    int scanTXT(const std::string& inputFile);
    int generateCSV(const std::string& outputFile);

 private:
    std::map<std::string, int> wordFrequencyMap;
};

#endif  // LAB0B_INCLUDE_CSVPARSER_H_
