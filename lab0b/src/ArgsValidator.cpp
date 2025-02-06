#include "ArgsValidator.h"
#include <stdexcept>

void ArgsValidator::validate(int argc, char* argv[]) {
    if (argc != 3) {
        throw std::invalid_argument("Error: got " +
            std::to_string(argc - 1) +
            " arguments, expected 2\nUsage: " +
            argv[0] + " input.txt output.csv");
    }
}
