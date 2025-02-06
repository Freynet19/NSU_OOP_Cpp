#include "argValidator.h"
#include <vector>
#include <string>
#include "exceptions.h"

void ArgValidator::validateArgs(int argc, char *argv[],
    std::string& configFile, std::string& outputFile,
    std::vector<std::string>& inputFiles) {
    if (argc < 4) {
        throw InvalidArgumentException(
            "Not enough arguments. Use -h for help.");
    }

    configFile = argv[1];
    checkFileExtension(configFile, ".txt");

    outputFile = argv[2];
    checkFileExtension(outputFile, ".wav");

    for (int i = 3; i < argc; ++i) {
        checkFileExtension(argv[i], ".wav");
        inputFiles.emplace_back(argv[i]);
    }
}

void ArgValidator::checkFileExtension(
    const std::string& filename, const std::string& expectedExtension) {
    std::filesystem::path path(filename);
    if (path.extension() != expectedExtension) {
        throw InvalidArgumentException("File '" + filename +
            "' must have extension '" + expectedExtension + "'.");
    }
}
