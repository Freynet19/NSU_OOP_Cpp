#include "LRUCache.h"

#include "ValueNotFound.h"

LRUCache::LRUCache(int cap): capacity(cap) {}

uint64 LRUCache::get(int key) {
    if (cMap.find(key) == cMap.end()) {
        throw ValueNotFound();
    }
    cList.splice(cList.begin(), cList, cMap[key]);
    cMap[key] = cList.begin();
    return cMap[key]->second;
}

uint64 LRUCache::operator[](int key) {
    return get(key);
}

void LRUCache::put(int key, uint64 value) {
    try {
        get(key);
    } catch (ValueNotFound&) {
        if (cList.size() >= capacity) {
            cMap.erase(cList.back().first);
            cList.pop_back();
        }
        cList.emplace_front(key, value);
        cMap[key] = cList.begin();
    }
}
