#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDFIBARG_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDFIBARG_H_

#include "InvalidArgument.h"

class InvalidFibNumberArgumentException: public InvalidArgumentException {
 public:
    explicit InvalidFibNumberArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDFIBARG_H_
