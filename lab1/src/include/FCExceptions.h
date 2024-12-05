#ifndef LAB1_SRC_INCLUDE_FCEXCEPTIONS_H_
#define LAB1_SRC_INCLUDE_FCEXCEPTIONS_H_

#include <stdexcept>

class InvalidArgumentException: public std::invalid_argument {
 public:
    explicit InvalidArgumentException(const char* message) :
        std::invalid_argument(message) {}
};

class UnprocessableArgumentException: public InvalidArgumentException {
 public:
    explicit UnprocessableArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

class InvalidCapacityArgumentException : public InvalidArgumentException {
 public:
    explicit InvalidCapacityArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

class InvalidTypeArgumentException: public InvalidArgumentException {
 public:
    explicit InvalidTypeArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

class InvalidFibNumberArgumentException: public InvalidArgumentException {
 public:
    explicit InvalidFibNumberArgumentException(const char* message)
        : InvalidArgumentException(message) {}
};

#endif  // LAB1_SRC_INCLUDE_FCEXCEPTIONS_H_
