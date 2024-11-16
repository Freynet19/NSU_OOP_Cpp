#include "LFUCache.h"

#include <map>

LFUCache::LFUCache(int cap): capacity(cap) {}

uint64 LFUCache::get(int key) {
    if (cMap.find(key) != cMap.end()) {
        auto it = cMap[key].second;
        int newFreq = it->second + 1;
        cSet.erase(it);
        cMap[key].second = cSet.emplace(newFreq, key).first;
        return cMap[key].first;
    }
    return 0;
}

uint64 LFUCache::operator[](int key) {
    return get(key);
}

void LFUCache::put(int key, uint64 value) {
    if (cMap.find(key) == cMap.end()) {
        if (cSet.size() >= capacity) {
            auto it = cSet.begin();
            cMap.erase(it->second);
            cSet.erase(it);
        }
        cMap[key] = std::make_pair(value, cSet.emplace(1, key).first);
    } else {
        auto it = cMap[key].second;
        int newFreq = it->second + 1;
        cSet.erase(it);
        cMap[key].second = cSet.emplace(newFreq, key).first;
    }
}
