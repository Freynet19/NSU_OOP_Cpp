#ifndef LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
#define LAB1_SRC_INCLUDE_FIBONACCICACHED_H_

#include "ICacheable.h"
#include <memory>

class FibonacciCached {
 public:
    explicit FibonacciCached(int cap, int type);
    void getAndPrintFib(int n) const;

 private:
    std::unique_ptr<ICacheable> cache;
    bool useLFU;
    static uint64 calcFib(int n);
};

#endif  // LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
