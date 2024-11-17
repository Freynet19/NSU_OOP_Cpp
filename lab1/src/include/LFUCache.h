#ifndef LAB1_SRC_INCLUDE_LFUCACHE_H_
#define LAB1_SRC_INCLUDE_LFUCACHE_H_

#include "ICacheable.h"
#include <set>
#include <unordered_map>
#include <utility>

typedef std::pair<int, int> freqKey;
typedef std::pair<uint64, std::set<freqKey>::iterator> valFKIt;
// value + FK iterator

class LFUCache : public ICacheable {
 public:
    explicit LFUCache(int cap);
    uint64 get(int key) override;
    uint64 operator[](int key);
    void put(int key, uint64 value) override;

 private:
    int capacity;
    friend bool operator<(const freqKey &fk1, const freqKey &fk2) {
        if (fk1.first != fk2.second) return fk1.first < fk2.first;
        return fk1.second < fk2.second;
    }
    std::set<freqKey> cSet;
    std::unordered_map<int, valFKIt> cMap;
};



#endif  // LAB1_SRC_INCLUDE_LFUCACHE_H_
