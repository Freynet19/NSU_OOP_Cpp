#ifndef LAB3_SRC_INCLUDE_CONVERTERFACTORY_H_
#define LAB3_SRC_INCLUDE_CONVERTERFACTORY_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <vector>

#include "IConverter.h"

class ConverterFactory {
 public:
    using ConverterCreator = std::function<
        std::unique_ptr<IConverter>(std::istringstream&)>;

    explicit ConverterFactory(const std::vector<std::string>& inputFiles);

    std::unique_ptr<IConverter> createConverter(const std::string& name,
        std::istringstream& iss);

    void printHelp();

 private:
    void registerConverter(const std::string& name, ConverterCreator&& creator,
        const std::string& description, const std::string& parameters,
        const std::string& example);

    std::unordered_map<std::string, ConverterCreator> creators;
    std::vector<std::string> inputFiles;

    struct ConverterInfo {
        std::string name;
        std::string description;
        std::string parameters;
        std::string example;
    };

    std::vector<ConverterInfo> convertersInfo;
};

#endif  // LAB3_SRC_INCLUDE_CONVERTERFACTORY_H_
