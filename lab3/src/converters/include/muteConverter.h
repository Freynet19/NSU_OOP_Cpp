#ifndef LAB3_SRC_CONVERTERS_INCLUDE_MUTECONVERTER_H_
#define LAB3_SRC_CONVERTERS_INCLUDE_MUTECONVERTER_H_

#include "IConverter.h"

class MuteConverter : public IConverter {
 public:
    MuteConverter(int startSec, int endSec);
    void apply(std::vector<int16_t> &samples) override;

 private:
    int start, end;
};

#endif  // LAB3_SRC_CONVERTERS_INCLUDE_MUTECONVERTER_H_
