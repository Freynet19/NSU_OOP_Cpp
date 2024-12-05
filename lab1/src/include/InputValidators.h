#ifndef LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_
#define LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_

#include <map>
#include <memory>

enum class FCArgumentType { CACHE_CAPACITY, CACHE_TYPE, FIB_NUMBER };

class IValidator {
 public:
    virtual void validate(int arg) = 0;
    virtual ~IValidator() = default;
    IValidator() = default;
    IValidator(const IValidator&) = delete;
    IValidator(IValidator&&) = delete;
    IValidator& operator=(const IValidator&) = delete;
    IValidator& operator=(IValidator&&) = delete;

 protected:
    const char* belowMinExcMsg =
        "argument is below minimum allowed value! Try again.";
    const char* aboveMaxExcMsg =
        "argument is above maximum allowed value! Try again.";
};

class CacheCapacityValidator : public IValidator {
 public:
    void validate(int arg) override;

 private:
    int minValue = 0;
    int maxValue = 1000;
};

class CacheTypeValidator : public IValidator {
 public:
    void validate(int arg) override;

 private:
    int minValue = 0;
    int maxValue = 2;
};

class FibNumberValidator : public IValidator {
 public:
    void validate(int arg) override;

 private:
    int minValue = 0;
    int maxValue = 93;
};

class InputValidator {
 public:
    InputValidator(int value, FCArgumentType type);
    void validate() const;

 private:
    int arg;
    FCArgumentType argType;
    std::unique_ptr<IValidator> validator_;
};

#endif  // LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_
