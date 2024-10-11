#include <iostream>
#include "../include/Reader.h"
#include "../include/Parser.h"
#include "../include/Writer.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: got " << argc - 1
        << " arguments, expected 2" << std::endl;
        std::cerr << "Usage: " << argv[0]
        << " input.txt output.csv" << std::endl;
        return 1;
    }

    Reader reader;
    if (reader.readTXT(argv[1]) != 0) return 1;
    Parser parser;
    parser.parseForCSV(reader.getWordMap());
    if (Writer::writeCSV(argv[2],
        parser.getWordList(), parser.getWordsCount()) != 0) return 1;

    std::cout << "CSV file successfully created." << std::endl;
    return 0;
}
