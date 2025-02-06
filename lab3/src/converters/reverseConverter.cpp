#include "reverseConverter.h"
#include <algorithm>

ReverseConverter::ReverseConverter() {}

void ReverseConverter::apply(std::vector<int16_t>& samples) {
    std::reverse(samples.begin(), samples.end());
}
