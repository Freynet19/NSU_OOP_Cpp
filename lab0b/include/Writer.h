#ifndef LAB0B_INCLUDE_WRITER_H_
#define LAB0B_INCLUDE_WRITER_H_

#include <string>
#include <vector>
#include <utility>

class Writer {
 public:
    static int writeCSV(const std::string& outputFile,
      const std::vector<std::pair<std::string, int>>& wordList, int wordsCount);
};

#endif  // LAB0B_INCLUDE_WRITER_H_
