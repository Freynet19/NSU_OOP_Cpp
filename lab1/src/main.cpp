#include <iostream>
#include "FCInputHandler.h"
#include "FibonacciCached.h"

int main() {
    std::cout << "Welcome to LRU/LFU-cached Fibonacci Calculator!" << std::endl;
    while (true) {
        const int cap = FCInputHandler::getCacheCapacity();
        if (cap == 0) break;
        const СacheType type = FCInputHandler::getCacheType();
        if (type == СacheType::EXIT) break;
        FibonacciCached fc(cap, type);
        while (true) {
            const int arg = FCInputHandler::getFibArgument();
            if (arg == 0) break;
            fc.getAndPrintFib(arg);
        }
    }
    std::cout << "Goodbye! Exiting program..." << std::endl;
    return 0;
}
