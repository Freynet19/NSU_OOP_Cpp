#ifndef LAB0B_INCLUDE_READER_H_
#define LAB0B_INCLUDE_READER_H_

#include <map>
#include <string>

class Reader {
 public:
    int readTXT(const std::string& inputFile);
    [[nodiscard]] std::map<std::string, int> getWordMap() const;

 private:
    std::map<std::string, int> wordFrequencyMap;
};

#endif  // LAB0B_INCLUDE_READER_H_
