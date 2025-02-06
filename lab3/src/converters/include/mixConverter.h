#ifndef LAB3_SRC_CONVERTERS_INCLUDE_MIXCONVERTER_H_
#define LAB3_SRC_CONVERTERS_INCLUDE_MIXCONVERTER_H_

#include "IConverter.h"
#include <string>
#include <vector>

class MixConverter : public IConverter {
 public:
    MixConverter(const std::string &otherFile, int insertPos);
    void apply(std::vector<int16_t> &samples) override;

 private:
    std::vector<int16_t> mixSamples;
    int insertPosition;
};

#endif  // LAB3_SRC_CONVERTERS_INCLUDE_MIXCONVERTER_H_
