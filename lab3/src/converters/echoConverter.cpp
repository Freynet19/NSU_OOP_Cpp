#include "echoConverter.h"
#include <limits>
#include "wavFile.h"

EchoConverter::EchoConverter(int delayMs, int decay)
    : delay(delayMs), decay(decay) {}

void EchoConverter::apply(std::vector<int16_t> &samples) {
    size_t delaySamples = (delay * WavFile::defaultSampleRate) / 1000;
    for (size_t i = delaySamples; i < samples.size(); i++) {
        int32_t rawEchoSample =
            static_cast<int32_t>(samples[i - delaySamples]) * decay / 100;
        int32_t result = static_cast<int32_t>(samples[i]) + rawEchoSample;

        if (result > std::numeric_limits<int16_t>::max()) {
            result = std::numeric_limits<int16_t>::max();
        } else if (result < std::numeric_limits<int16_t>::min()) {
            result = std::numeric_limits<int16_t>::min();
        }

        samples[i] = static_cast<int16_t>(result);
    }
}
