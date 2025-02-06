#include "InputValidators.h"

#include <memory>
#include "InvalidCapArg.h"
#include "InvalidTypeArg.h"
#include "InvalidFibArg.h"

ProgramArgumentsValidator::ProgramArgumentsValidator(
    int value, FCArgumentType type): arg(value), argType(type) {
    switch (argType) {
    case(FCArgumentType::CACHE_CAPACITY):
        validator_ = std::make_unique<CacheCapacityValidator>();
        break;
    case(FCArgumentType::CACHE_TYPE):
        validator_ = std::make_unique<CacheTypeValidator>();
        break;
    case(FCArgumentType::FIB_NUMBER):
        validator_ = std::make_unique<FibNumberValidator>();
        break;
    }
}

void ProgramArgumentsValidator::validate() const {
    return validator_->validate(arg);
}

void CacheCapacityValidator::validate(int arg) {
    if (arg < minValue) throw InvalidCapacityArgumentException(belowMinExcMsg);
    if (arg > maxValue) throw InvalidCapacityArgumentException(aboveMaxExcMsg);
}

void CacheTypeValidator::validate(int arg) {
    if (arg < minValue) throw InvalidTypeArgumentException(belowMinExcMsg);
    if (arg > maxValue) throw InvalidTypeArgumentException(aboveMaxExcMsg);
}

void FibNumberValidator::validate(int arg) {
    if (arg < minValue) throw InvalidFibNumberArgumentException(belowMinExcMsg);
    if (arg > maxValue) throw InvalidFibNumberArgumentException(aboveMaxExcMsg);
}
