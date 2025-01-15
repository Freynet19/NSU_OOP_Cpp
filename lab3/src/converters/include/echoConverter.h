#ifndef LAB3_SRC_CONVERTERS_INCLUDE_ECHOCONVERTER_H_
#define LAB3_SRC_CONVERTERS_INCLUDE_ECHOCONVERTER_H_

#include "IConverter.h"

class EchoConverter : public IConverter {
 public:
    EchoConverter(int delayMs, int decay);
    void apply(std::vector<int16_t> &samples) override;

 private:
    int delay, decay;
};

#endif  // LAB3_SRC_CONVERTERS_INCLUDE_ECHOCONVERTER_H_
