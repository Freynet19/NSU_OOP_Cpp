#include "rules.h"
#include "ioExceptions.h"
#include <vector>
#include <string>

Rules::Rules(const std::string &ruleStr): ruleStr(ruleStr) {
    birth.clear();
    survive.clear();
    auto pos = ruleStr.find('/');
    if (pos == std::string::npos) {
        throw ruleParsingException(
            "Invalid rule format (no slash): " + ruleStr);
    }

    std::string bPart = ruleStr.substr(0, pos);
    std::string sPart = ruleStr.substr(pos + 1);

    if (!bPart.empty() && bPart[0] == 'B') {
        for (size_t i = 1; i < bPart.size(); ++i) {
            if (isdigit(bPart[i])) {
                birth.push_back(bPart[i] - '0');
            } else {
                throw ruleParsingException("Invalid birth rule: " + ruleStr);
            }
        }
    } else {
        throw ruleParsingException("Invalid rule format (no B): " + ruleStr);
    }

    if (sPart.size() > 0 && sPart[0] == 'S') {
        for (size_t i = 1; i < sPart.size(); ++i) {
            if (isdigit(sPart[i])) {
                survive.push_back(sPart[i] - '0');
            } else {
                throw ruleParsingException("Invalid survive rule: " + ruleStr);
            }
        }
    } else {
        throw ruleParsingException("Invalid rule format (no S): " + ruleStr);
    }
}

bool Rules::shouldLive(bool currentlyAlive, int neighbors) const {
    if (currentlyAlive) {
        return std::ranges::find(survive, neighbors) != survive.end();
    }
    return std::ranges::find(birth, neighbors) != birth.end();
}

std::string Rules::getString() const { return ruleStr; }
