#ifndef LAB0B_SRC_INCLUDE_READER_H_
#define LAB0B_SRC_INCLUDE_READER_H_

#include <map>
#include <string>

class Reader {
 public:
    explicit Reader(const char* inputTXT);
    void readTXT();
    [[nodiscard]] std::map<std::string, int> getWordMap() const;

 private:
    std::string inputFile;
    std::map<std::string, int> wordFrequencyMap;
};

#endif  // LAB0B_SRC_INCLUDE_READER_H_
