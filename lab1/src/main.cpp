#include <iostream>
#include "FCInputHandler.h"
#include "FibonacciCached.h"

int main() {
    std::cout << "Welcome to LRU/LFU-cached Fibonacci Calculator!" << std::endl;
    while (true) {
        const int cap = FCInputHandler::getCacheCapacity();
        if (!cap) break;
        const int type = FCInputHandler::getCacheType();
        if (!type) break;
        FibonacciCached fc(cap, type);
        while (true) {
            const int arg = FCInputHandler::getFibArgument();
            if (!arg) break;
            fc.getAndPrintFib(arg);
        }
    }
    std::cout << "Goodbye! Exiting program..." << std::endl;
    return 0;
}
