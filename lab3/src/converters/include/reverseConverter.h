#ifndef LAB3_SRC_CONVERTERS_INCLUDE_REVERSECONVERTER_H_
#define LAB3_SRC_CONVERTERS_INCLUDE_REVERSECONVERTER_H_

#include "IConverter.h"

class ReverseConverter : public IConverter {
 public:
    ReverseConverter();
    void apply(std::vector<int16_t> &samples) override;
};

#endif  // LAB3_SRC_CONVERTERS_INCLUDE_REVERSECONVERTER_H_
