#include "cfgParser.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <utility>
#include <vector>
#include <string>
#include "converterFactory.h"
#include "exceptions.h"

ConfigParser::ConfigParser(
    std::string fname, const std::vector<std::string>& inputFiles)
    : filename(std::move(fname)), inputFiles(inputFiles) {}

std::vector<std::unique_ptr<IConverter>> ConfigParser::parseConverters() const {
    std::ifstream file(filename);
    if (!file.is_open()) throw ConfigError(
        std::string("Error opening config file: ") +
        std::filesystem::absolute(filename).string());

    ConverterFactory factory(inputFiles);
    std::vector<std::unique_ptr<IConverter>> converters;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        converters.push_back(factory.createConverter(cmd, iss));
    }
    return converters;
}
