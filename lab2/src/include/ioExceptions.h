#ifndef LAB2_SRC_INCLUDE_IOEXCEPTIONS_H_
#define LAB2_SRC_INCLUDE_IOEXCEPTIONS_H_

#include <stdexcept>
#include <string>

class openFileException : public std::runtime_error {
 public:
    explicit openFileException(const std::string& message)
        : std::runtime_error(message) {}
};

class invalidInputFileFormat : public std::runtime_error {
 public:
    explicit invalidInputFileFormat()
        : std::runtime_error("Invalid file format. Expected '#Life 1.06'.") {}
};

class ruleParsingException : public std::runtime_error {
 public:
    explicit ruleParsingException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif  // LAB2_SRC_INCLUDE_IOEXCEPTIONS_H_
