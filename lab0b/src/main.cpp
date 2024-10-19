#include <iostream>
#include "../include/FrequencyParser.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: got " << argc - 1
        << " arguments, expected 2" << std::endl;
        std::cerr << "Usage: " << argv[0]
        << " input.txt output.csv" << std::endl;
        return 1;
    }

    FrequencyParser parser(argv[1], argv[2]);
    if (parser.GetWordFrequency() != 0) return 1;

    return 0;
}
