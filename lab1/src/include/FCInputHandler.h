#ifndef LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
#define LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_

#include "FibonacciCached.h"
#include "InputValidators.h"

class FCInputHandler {
 public:
    static int getCacheCapacity();
    static СacheType getCacheType();
    static int getFibArgument();
    FCInputHandler() = delete;

 private:
    static int getIntFromCin(FCArgumentType argType);
};

#endif  // LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
