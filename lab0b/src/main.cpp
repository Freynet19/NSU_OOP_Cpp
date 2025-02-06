#include <iostream>
#include <memory>
#include "ArgsValidator.h"
#include "Reader.h"
#include "FrequencyParser.h"
#include "Writer.h"

int main(int argc, char* argv[]) {
    try {
        ArgsValidator::validate(argc, argv);

        auto input_reader = std::make_unique<Reader>(argv[1]);
        auto output_writer = std::make_unique<CSVWriter>(argv[2]);

        FrequencyParser parser(input_reader.get(), output_writer.get());
        parser.parseAndWrite();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
