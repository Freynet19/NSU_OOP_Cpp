#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <map>
#include <string>

class CsvParser {
public:
    int scanTXT(const std::string& inputFile);
    int generateCSV(const std::string& outputFile);

private:
    std::map<std::string, int> wordFrequencyMap;
};

#endif
