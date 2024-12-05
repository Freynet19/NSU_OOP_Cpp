#ifndef LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
#define LAB1_SRC_INCLUDE_FIBONACCICACHED_H_

#include "ICacheable.h"
#include <memory>

enum class СacheType { EXIT = 0, LRU = 1, LFU = 2 };

class FibonacciCached {
 public:
    explicit FibonacciCached(int cap, СacheType type);
    void getAndPrintFib(int n) const;

 private:
    std::unique_ptr<ICacheable> cache;
    СacheType type;
    static uint64 calcFib(int n);
};

#endif  // LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
