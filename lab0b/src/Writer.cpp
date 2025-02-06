#include "Writer.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

CSVWriter::CSVWriter(const char* outputCSV): outputFile(outputCSV) {}

void CSVWriter::writeCSV(
    std::vector<std::pair<std::string, int>> const& wordList,
    const size_t wordsCount) const {
    std::ofstream fileOut(outputFile);
    if (!fileOut.is_open()) {
        throw std::runtime_error("Error opening output file: " +
            std::filesystem::absolute(outputFile).string());
    }

    fileOut << "Word,Frequency,Frequency(%)" << std::endl;
    for (const auto& [fst, snd] : wordList) {
        fileOut << fst << ","
                << snd << ","
                << snd * 100.0 / static_cast<double>(wordsCount) << std::endl;
    }

    std::cout << "CSV file successfully created: "
        << std::filesystem::absolute(outputFile).string() << std::endl;

    fileOut.close();
}
