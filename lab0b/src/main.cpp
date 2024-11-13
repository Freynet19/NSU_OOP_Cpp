#include <iostream>

#include "Reader.h"
#include "FrequencyParser.h"
#include "Writer.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            throw std::invalid_argument("Error: got " +
                std::to_string(argc-1) +
                " arguments, expected 2\nUsage: " +
                argv[0] + " input.txt output.csv");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    const auto input_reader = new Reader(argv[1]);
    const auto output_writer = new CSVWriter(argv[2]);
    auto parser = FrequencyParser(input_reader, output_writer);

    try {
        parser.parseAndWrite();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    delete input_reader;
    delete output_writer;
    return 0;
}
