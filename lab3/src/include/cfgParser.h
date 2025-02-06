#ifndef LAB3_SRC_INCLUDE_CFGPARSER_H_
#define LAB3_SRC_INCLUDE_CFGPARSER_H_

#include <memory>
#include <string>
#include <vector>

#include "IConverter.h"

class ConfigParser {
 public:
    explicit ConfigParser(std::string fname,
        const std::vector<std::string>& inputFiles);

    [[nodiscard]] std::vector<std::unique_ptr<IConverter>>
        parseConverters() const;

 private:
    std::string filename;
    std::vector<std::string> inputFiles;
};

#endif  // LAB3_SRC_INCLUDE_CFGPARSER_H_
