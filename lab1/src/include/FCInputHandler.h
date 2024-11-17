#ifndef LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
#define LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_

class FCInputHandler {
 public:
    static int getCacheCapacity();
    static int getCacheType();
    static int getFibArgument();

 private:
    static int getIntFromCin(int argType);
};

#endif  // LAB1_SRC_INCLUDE_FCINPUTHANDLER_H_
