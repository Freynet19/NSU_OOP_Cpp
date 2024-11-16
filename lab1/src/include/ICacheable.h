#ifndef ICACHEABLE_H
#define ICACHEABLE_H

typedef unsigned long long uint64;

class ICacheable {
 public:
    virtual uint64 get(int key) = 0;
    virtual void put(int key, uint64 value) = 0;
    virtual ~ICacheable() = default;
};

#endif //ICACHEABLE_H
