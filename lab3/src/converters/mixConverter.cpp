#include "mixConverter.h"
#include <string>
#include "wavFile.h"

MixConverter::MixConverter(const std::string &otherFile, int insertPos)
    : insertPosition(insertPos) {
    WavFile file(otherFile);
    file.read();
    mixSamples = file.getSamples();
}

void MixConverter::apply(std::vector<int16_t> &samples) {
    size_t insertSample = insertPosition * WavFile::defaultSampleRate;
    for (size_t i = 0; i < mixSamples.size() &&
        insertSample + i < samples.size(); i++) {
        int32_t rawMixedSample =
            static_cast<int32_t>(samples[insertSample + i]) +
            static_cast<int32_t>(mixSamples[i]);
        samples[insertSample + i] = static_cast<int16_t>(rawMixedSample / 2);
    }
}
