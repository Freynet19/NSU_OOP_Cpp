#ifndef LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_
#define LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_

#include <map>
#include <memory>

enum class FCArgumentType { CACHE_CAPACITY, CACHE_TYPE, FIB_NUMBER };

class IntegerValidator {
 public:
    virtual void validate(int arg) = 0;
    virtual ~IntegerValidator() = default;
    IntegerValidator() = default;
    IntegerValidator(const IntegerValidator&) = delete;
    IntegerValidator(IntegerValidator&&) = delete;
    IntegerValidator& operator=(const IntegerValidator&) = delete;
    IntegerValidator& operator=(IntegerValidator&&) = delete;

 protected:
    const char* belowMinExcMsg =
        "argument is below minimum allowed value! Try again.";
    const char* aboveMaxExcMsg =
        "argument is above maximum allowed value! Try again.";
};

class CacheCapacityValidator : public IntegerValidator {
 public:
    void validate(int arg) override;

 private:
    static constexpr int minValue = 0;
    static constexpr int maxValue = 1000;
};

class CacheTypeValidator : public IntegerValidator {
 public:
    void validate(int arg) override;

 private:
    static constexpr int minValue = 0;
    static constexpr int maxValue = 2;
};

class FibNumberValidator : public IntegerValidator {
 public:
    void validate(int arg) override;

 private:
    static constexpr int minValue = 0;
    static constexpr int maxValue = 93;
    // т.к. Fib(94) выходит за пределы uint64_t
};

class ProgramArgumentsValidator {
 public:
    ProgramArgumentsValidator(int value, FCArgumentType type);
    void validate() const;

 private:
    int arg;
    FCArgumentType argType;
    std::unique_ptr<IntegerValidator> validator_;
};

#endif  // LAB1_SRC_INCLUDE_INPUTVALIDATORS_H_
