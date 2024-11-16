#ifndef _LRU_CACHE_H_
#define _LRU_CACHE_H_

#include "ICacheable.h"
#include <list>
#include <unordered_map>

class LRUCache : public ICacheable {
 public:
    explicit LRUCache(int cap);
    uint64 get(int key) override;
    uint64 operator[](int key);
    void put(int key, uint64 value) override;

 private:
    int capacity;
    std::list<std::pair<int, uint64>> cList;
    std::unordered_map<int, std::list<std::pair<int, uint64>>::iterator> cMap;
};

#endif // _LRU_CACHE_H_