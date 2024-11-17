#ifndef FIBONACCI_H
#define FIBONACCI_H
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

#endif //FIBONACCI_H
