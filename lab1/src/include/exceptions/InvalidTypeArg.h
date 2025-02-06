#ifndef LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDTYPEARG_H_
#define LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDTYPEARG_H_

#include "InvalidArgument.h"

class InvalidTypeArgumentException: public InvalidArgumentException {
 public:
    explicit InvalidTypeArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

#endif  // LAB1_SRC_INCLUDE_EXCEPTIONS_INVALIDTYPEARG_H_
