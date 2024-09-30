#include <iostream>
#include "../include/csvParser.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: "
                  << argv[0]
                  << " input.txt output.csv"
                  << std::endl;
        return 1;
    }

    CsvParser parser;
    if (parser.scanTXT(argv[1]) != 0) return 1;
    if (parser.generateCSV(argv[2]) != 0) return 1;

    std::cout << "CSV file successfully created." << std::endl;
    return 0;
}
