#include <iostream>
#include "../include/Parser.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: got " << argc - 1
        << " arguments, expected 2" << std::endl;
        std::cerr << "Usage: " << argv[0]
        << " input.txt output.csv" << std::endl;
        return 1;
    }

    Parser parser;
    if (parser.parseCSV(argv[1], argv[2]) != 0) return 1;

    std::cout << "CSV file successfully created." << std::endl;
    return 0;
}
