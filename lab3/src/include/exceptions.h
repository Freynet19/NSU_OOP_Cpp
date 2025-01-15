#ifndef LAB3_SRC_INCLUDE_EXCEPTIONS_H_
#define LAB3_SRC_INCLUDE_EXCEPTIONS_H_

#include <string>
#include <utility>

class SoundProcessorException : public std::exception {
 protected:
    std::string message;

 public:
    explicit SoundProcessorException(std::string  msg)
        : message(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class ConfigError : public SoundProcessorException {
 public:
    explicit ConfigError(const std::string& msg)
        : SoundProcessorException("Configuration error: " + msg) {}
};

class InvalidConverterArgument : public ConfigError {
 public:
    explicit InvalidConverterArgument(const std::string& issStr)
        : ConfigError("Invalid arguments for converter: " + issStr) {}
};

class UnsupportedFormatException : public SoundProcessorException {
 public:
    UnsupportedFormatException()
        : SoundProcessorException("Unsupported WAV file format.") {}
};

class InvalidArgumentException : public SoundProcessorException {
 public:
    explicit InvalidArgumentException(const std::string& msg)
        : SoundProcessorException("Invalid argument: " + msg) {}
};

class FileIOException : public SoundProcessorException {
 public:
    explicit FileIOException(const std::string& msg)
        : SoundProcessorException("File I/O error: " + msg) {}
};

#endif  // LAB3_SRC_INCLUDE_EXCEPTIONS_H_
