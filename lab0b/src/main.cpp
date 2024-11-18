#include <iostream>

#include "Reader.h"
#include "FrequencyParser.h"
#include "Writer.h"

int main(int argc, char* argv[]) {
    try {
        FrequencyParser::validateArgs(argc, argv);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 0;
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
