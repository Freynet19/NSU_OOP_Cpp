#ifndef LAB3_SRC_INCLUDE_ICONVERTER_H_
#define LAB3_SRC_INCLUDE_ICONVERTER_H_

#include <cstdint>
#include <string>
#include <vector>

class IConverter {
 public:
    virtual ~IConverter() = default;
    virtual void apply(std::vector<int16_t> &samples) = 0;
};

#endif  // LAB3_SRC_INCLUDE_ICONVERTER_H_
