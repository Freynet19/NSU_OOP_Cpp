#include "FibonacciCached.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>

FibonacciCached::FibonacciCached(int cap, int type) {
    if (type == 1) {
        useLFU = false;
        cache = std::make_unique<LRUCache>(LRUCache(cap));
        std::cout << "Using LRU cache..." << std::endl;
    } else {
        useLFU = true;
        cache = std::make_unique<LFUCache>(LFUCache(cap));
        std::cout << "Using LFU cache..." << std::endl;
    }
}

void FibonacciCached::getAndPrintFib(int n) const {
    uint64 value = cache->get(n);
    if (value == 0) {
        std::cout << "Value not found in cache. Calculating..."
            << std::endl;
        value = calcFib(n);
        cache->put(n, value);
        std::cout << "Calculated value:\t  ";
    } else {
        std::cout << "Value found in cache: ";
    }
    std::cout << value << std::endl;
}

uint64 FibonacciCached::calcFib(int n) {
    // n is in [1, 93] always
    if (n <= 2) return 1;
    return calcFib(n - 1) + calcFib(n - 2);
}
