#ifndef FCINPUTRECEIVER_H
#define FCINPUTRECEIVER_H

class FCInputHandler {
 public:
    static int getCacheCapacity();
    static int getCacheType();
    static int getFibArgument();

 private:
    static int getIntFromCin(int argType);
};

#endif //FCINPUTRECEIVER_H
