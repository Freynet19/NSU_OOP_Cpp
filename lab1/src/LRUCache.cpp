#include "LRUCache.h"

LRUCache::LRUCache(int cap): capacity(cap) {}

uint64 LRUCache::get(int key) {
    if (cMap.find(key) != cMap.end()) {
        auto it = cMap[key];
        const uint64 value = it->second;
        cList.splice(cList.begin(), cList, it);
        cMap[key] = cList.begin();
        return value;
    }
    return 0;
}

uint64 LRUCache::operator[](int key) {
    return get(key);
}

void LRUCache::put(int key, uint64 value) {
    if (cMap.find(key) == cMap.end()) {
        if (cList.size() >= capacity) {
            cMap.erase(cList.back().first);
            cList.pop_back();
        }
        cList.emplace_front(key, value);
    } else {
        cList.splice(cList.begin(), cList, cMap[key]);
    }
    cMap[key] = cList.begin();
}
