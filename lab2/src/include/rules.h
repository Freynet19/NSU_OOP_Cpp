#ifndef LAB2_SRC_INCLUDE_RULES_H_
#define LAB2_SRC_INCLUDE_RULES_H_

#include <string>
#include <vector>

class Rules {
 public:
    explicit Rules(const std::string &ruleStr);

    bool shouldLive(bool currentlyAlive, int neighbors) const;
    [[nodiscard]] std::string getString() const;

 private:
    std::vector<int> birth;
    std::vector<int> survive;
    std::string ruleStr;
};

#endif  // LAB2_SRC_INCLUDE_RULES_H_
