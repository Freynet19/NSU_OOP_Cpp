#include "LRUCache.h"

LRUCache::LRUCache(int cap): capacity(cap) {}

uint64 LRUCache::get(int key) {
    if (cMap.find(key) != cMap.end()) {
        cList.splice(cList.begin(), cList, cMap[key]);
        cMap[key] = cList.begin();
        return cMap[key]->second;
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
    } else {
        cList.erase(cMap[key]);
    }

    cList.emplace_front(key, value);
    cMap[key] = cList.begin();
}
