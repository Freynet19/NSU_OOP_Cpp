#ifndef LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
#define LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
#include "ICacheable.h"

class FibonacciCached {
 public:
    explicit FibonacciCached(int cap, int type);
    ~FibonacciCached();
    void getAndPrintFib(int n) const;

 private:
    ICacheable* cache;
    bool useLFU;
    static uint64 calcFib(int n);

    FibonacciCached(const FibonacciCached&);
    FibonacciCached& operator=(const FibonacciCached&);
    FibonacciCached(FibonacciCached&&) noexcept;
    FibonacciCached& operator=(FibonacciCached&&) noexcept;
};

#endif  // LAB1_SRC_INCLUDE_FIBONACCICACHED_H_
