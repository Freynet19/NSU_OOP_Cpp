#ifndef LAB0B_SRC_INCLUDE_WRITER_H_
#define LAB0B_SRC_INCLUDE_WRITER_H_

#include <string>
#include <vector>
#include <utility>

class CSVWriter {
 public:
    explicit CSVWriter(const char* outputCSV);
    void writeCSV(const std::vector<std::pair<std::string, int>>& wordList,
        int wordsCount) const;
 private:
    std::string outputFile;
};

#endif  // LAB0B_SRC_INCLUDE_WRITER_H_
