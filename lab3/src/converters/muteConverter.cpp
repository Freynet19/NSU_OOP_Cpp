#include "muteConverter.h"
#include "wavFile.h"

MuteConverter::MuteConverter(int startSec, int endSec)
    : start(startSec), end(endSec) {}

void MuteConverter::apply(std::vector<int16_t> &samples) {
    size_t startSample = start * WavFile::defaultSampleRate;
    size_t endSample = end * WavFile::defaultSampleRate;

    if (startSample > samples.size()) return;
    if (endSample > samples.size()) endSample = samples.size();

    for (size_t i = startSample; i < endSample; i++) {
        samples[i] = 0;
    }
}
