#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDARGUMENT_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDARGUMENT_H_

#include <stdexcept>

class InvalidArgumentException: public std::invalid_argument {
 public:
    explicit InvalidArgumentException(const char* message) :
        std::invalid_argument(message) {}
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDARGUMENT_H_
