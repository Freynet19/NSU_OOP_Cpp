#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_UNPROCESSABLEARG_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_UNPROCESSABLEARG_H_

#include "InvalidArgument.h"

class UnprocessableArgumentException: public InvalidArgumentException {
 public:
    explicit UnprocessableArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_UNPROCESSABLEARG_H_
