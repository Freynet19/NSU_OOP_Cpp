#ifndef LAB1_SRC_INCLUDE_ICACHE_H_
#define LAB1_SRC_INCLUDE_ICACHE_H_

#include <cstdint>

typedef uint64_t uint64;

class ICache {
 public:
    virtual uint64 get(int key) = 0;
    virtual void put(int key, uint64 value) = 0;
    virtual ~ICache() = default;
};

#endif  // LAB1_SRC_INCLUDE_ICACHE_H_
