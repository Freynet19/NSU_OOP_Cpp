#ifndef LAB3_SRC_INCLUDE_ARGVALIDATOR_H_
#define LAB3_SRC_INCLUDE_ARGVALIDATOR_H_

#include <vector>
#include <string>
#include <filesystem>

class ArgValidator {
 public:
    static void validateArgs(int argc, char *argv[],
        std::string& configFile, std::string& outputFile,
        std::vector<std::string>& inputFiles);

 private:
    static void checkFileExtension(const std::string& filename,
        const std::string& expectedExtension);
};

#endif  // LAB3_SRC_INCLUDE_ARGVALIDATOR_H_
