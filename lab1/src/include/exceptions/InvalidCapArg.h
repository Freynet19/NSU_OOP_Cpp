#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDCAPARG_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDCAPARG_H_

#include "InvalidArgument.h"

class InvalidCapacityArgumentException : public InvalidArgumentException {
 public:
    explicit InvalidCapacityArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDCAPARG_H_
