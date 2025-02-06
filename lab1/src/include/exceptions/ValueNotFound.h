#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_VALUENOTFOUND_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_VALUENOTFOUND_H_

#include <stdexcept>

class ValueNotFound : public std::exception {
 public:
    const char* what() const noexcept override { return ""; }
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_VALUENOTFOUND_H_
