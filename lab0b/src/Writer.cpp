#include "Writer.h"

#include <iostream>
#include <fstream>
#include <filesystem>

CSVWriter::CSVWriter(const char* outputCSV): outputFile(outputCSV) {}

void CSVWriter::writeCSV(
    std::vector<std::pair<std::string, int>> const& wordList,
    const int wordsCount) const {
    std::ofstream fileOut(outputFile);
    if (!fileOut.is_open()) {
        throw std::runtime_error("Error opening output file: " +
            std::filesystem::absolute(outputFile).string());
    }

    fileOut << "Word,Frequency,Frequency(%)" << std::endl;
    for (const auto& pair : wordList) {
        fileOut << pair.first << ","
                << pair.second << ","
                << pair.second * 100.0 / wordsCount << std::endl;
    }

    std::cout << "CSV file successfully created: "
    << std::filesystem::absolute(outputFile).string() << std::endl;

    fileOut.close();
}
