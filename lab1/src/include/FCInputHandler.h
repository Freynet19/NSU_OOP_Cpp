#ifndef LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
#define LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_

enum class FCInputType { CACHE_CAPACITY, CACHE_TYPE, FIB_NUMBER };

class FCInputHandler {
 public:
    static int getCacheCapacity();
    static int getCacheType();
    static int getFibArgument();
    FCInputHandler() = delete;

 private:
    static int getIntFromCin(FCInputType argType);
    constexpr static int minValue = 0;
    constexpr static int maxCapValue = 1000;
    constexpr static int maxTypeValue = 2;
    constexpr static int maxFibValue = 93;
};

#endif  // LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
