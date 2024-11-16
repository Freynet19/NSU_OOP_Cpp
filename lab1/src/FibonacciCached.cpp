#include "FibonacciCached.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>

FibonacciCached::FibonacciCached(int cap, int type) {
    if (type == 1) {
        useLFU = false;
        cache = new LRUCache(cap);
        std::cout << "Using LRU cache..." << std::endl;
    } else {
        useLFU = true;
        cache = new LFUCache(cap);
        std::cout << "Using LFU cache..." << std::endl;
    }
}

FibonacciCached::~FibonacciCached() { delete cache; }

void FibonacciCached::getAndPrintFib(int n) const {
    uint64 value = cache->get(n);
    if (value == 0) {
        std::cout << "Value not found in cache. Calculating..."
            << std::endl;
        value = calcFib(n);
        cache->put(n, value);
        std::cout << "Calculated value: ";
    }
    else std::cout << "Value found in cache: ";
    std::cout << value << std::endl;
}

uint64 FibonacciCached::calcFib(int n) {
    // n > 0 always
    if (n <= 2) return 1;
    uint64 pr2 = 1, pr1 = 1, cur = 2;
    for (int i = 3; i <= n; i++) {
        cur = pr1 + pr2;
        pr2 = pr1;
        pr1 = cur;
    }
    return cur;
    // return calcFib(n - 1) + calcFib(n - 2);
    // чтобы была более заметна разница по времени в сравнении с кэшем
}



