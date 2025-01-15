#include <iostream>
#include <string>
#include <vector>

#include "processor.h"
#include "converterFactory.h"
#include "exceptions.h"
#include "argValidator.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || std::string(argv[1]) == "-h") {
        ConverterFactory factory({});
        factory.printHelp();
        return EXIT_SUCCESS;
    }

    try {
        std::string configFile;
        std::string outputFile;
        std::vector<std::string> inputFiles;

        ArgValidator::validateArgs(argc, argv,
            configFile, outputFile, inputFiles);

        SoundProcessor processor(configFile, outputFile, inputFiles);
        processor.process();
    } catch (const SoundProcessorException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
