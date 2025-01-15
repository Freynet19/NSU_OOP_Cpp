#include "processor.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <utility>
#include <string>
#include "cfgParser.h"
#include "wavFile.h"
#include "exceptions.h"

SoundProcessor::SoundProcessor(std::string configFile, std::string outputFile,
                               std::vector<std::string> &inputFiles)
    : configFile(std::move(configFile)), outputFile(std::move(outputFile)),
        inputFiles(std::move(inputFiles)) {}

void SoundProcessor::process() const {
    try {
        ConfigParser parser(configFile, inputFiles);
        auto converters = parser.parseConverters();

        WavFile inputWav(inputFiles[0]);
        inputWav.read();

        auto outputSamples = inputWav.getSamples();
        for (const auto& converter : converters) {
            converter->apply(outputSamples);
        }

        WavFile outputWav(outputFile);
        outputWav.setSamples(std::move(outputSamples));
        outputWav.write(outputFile);

        std::cout << "Output file successfully created: " <<
            std::filesystem::absolute(outputFile) << std::endl;
    } catch (const SoundProcessorException&) {
        throw;
    } catch (const std::exception& e) {
        throw FileIOException(
            "Unexpected error during processing: " + std::string(e.what()));
    }
}
