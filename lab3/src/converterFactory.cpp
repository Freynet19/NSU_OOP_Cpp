#include "converterFactory.h"

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include "muteConverter.h"
#include "mixConverter.h"
#include "echoConverter.h"
#include "reverseConverter.h"
#include "exceptions.h"

int extractStreamIndex(const std::string& str) {
    if (str.empty() || str[0] != '$') {
        throw ConfigError("Invalid stream reference: " + str);
    }
    try {
        return std::stoi(str.substr(1));
    } catch (const std::invalid_argument&) {
        throw ConfigError("Invalid stream reference (not a number): " + str);
    } catch (const std::out_of_range&) {
        throw ConfigError("Stream index out of range: " + str);
    }
}

ConverterFactory::ConverterFactory(const std::vector<std::string>& inputFiles)
    : inputFiles(inputFiles) {
    registerConverter("mute", [](std::istringstream& iss) {
        int start, end;
        if (!(iss >> start >> end)) throw InvalidConverterArgument(iss.str());
        return std::make_unique<MuteConverter>(start, end);
    }, "Mute an interval", "<start> <end>", "mute 10 20");

    registerConverter("mix", [this](std::istringstream& iss) {
        std::string streamRef;
        int pos;
        if (!(iss >> streamRef >> pos))
            throw InvalidConverterArgument(iss.str());

        int streamIdx = extractStreamIndex(streamRef);

        if (streamIdx < 1 || streamIdx > this->inputFiles.size()) {
            throw ConfigError(
                "Invalid stream index: " + std::to_string(streamIdx));
        }

        std::string otherFile = this->inputFiles[streamIdx - 1];
        return std::make_unique<MixConverter>(otherFile, pos);
    }, "Mix two streams", "<stream> <pos>", "mix $2 10");

    registerConverter("echo", [](std::istringstream& iss) {
        int delay, decay;
        if (!(iss >> delay >> decay)) throw InvalidConverterArgument(iss.str());
        return std::make_unique<EchoConverter>(delay, decay);
    }, "Add echo effect", "<delay> <decay>", "echo 500 50");

    registerConverter("reverse", [](std::istringstream& iss) {
        return std::make_unique<ReverseConverter>();
    }, "Reverse track", "", "reverse");
}

void ConverterFactory::registerConverter(const std::string& name,
        ConverterCreator&& creator, const std::string& description,
        const std::string& parameters, const std::string& example) {
    creators[name] = std::move(creator);
    convertersInfo.push_back({name, description, parameters, example});
}

std::unique_ptr<IConverter> ConverterFactory::createConverter(
    const std::string& name, std::istringstream& iss) {
    if (creators.find(name) != creators.end()) {
        return creators[name](iss);
    }
    throw ConfigError("Unknown converter: " + name);
}

void ConverterFactory::printHelp() {
    std::cout << "Usage: sound_processor <config.txt> <output.wav> "
                 "<input1.wav> [<input2.wav> ...]" << std::endl;
    std::cout << "Available converters:" << std::endl;

    for (const auto& info : convertersInfo) {
        std::cout << "\t" << info.name << " " <<
            info.parameters << " - " << info.description <<
            " (e.g. " << info.example << ")" << std::endl;
    }
}
