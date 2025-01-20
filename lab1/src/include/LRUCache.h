#ifndef LAB1_SRC_INCLUDE_LRUCACHE_H_
#define LAB1_SRC_INCLUDE_LRUCACHE_H_

#include "ICache.h"
#include <list>
#include <unordered_map>
#include <utility>

class LRUCache : public ICache {
 public:
    explicit LRUCache(int cap);
    uint64 get(int key) override;
    uint64 operator[](int key);
    void put(int key, uint64 value) override;

 private:
    int capacity;
    std::list<std::pair<int, uint64>> cList;
    // list of pair<key, value> (tracking Least Recent elements)
    std::unordered_map<int, std::list<std::pair<int, uint64>>::iterator> cMap;
    // umap<key, iteratorToList> (access key->element)
};

#endif  // LAB1_SRC_INCLUDE_LRUCACHE_H_
