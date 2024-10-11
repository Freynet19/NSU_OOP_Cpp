#ifndef LAB0B_INCLUDE_PARSER_H_
#define LAB0B_INCLUDE_PARSER_H_

#include <map>
#include <string>
#include <vector>
#include <utility>

typedef std::vector<std::pair<std::string, int>> wordList;

class Parser {
 public:
    void parseForCSV(const std::map<std::string, int>& wordFrequencyMap);
    [[nodiscard]] wordList getWordList() const;
    [[nodiscard]] int getWordsCount() const;

 private:
    wordList sortedList;
    int wordsCount = 0;
};

#endif  // LAB0B_INCLUDE_PARSER_H_
