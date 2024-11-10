#include "./include/Writer.h"

#include <iostream>
#include <fstream>
#include <filesystem>

int Writer::writeCSV(const std::string& outputFile,
                     std::vector<std::pair<std::string, int>> const& wordList,
                     const int wordsCount) {
    std::ofstream fileOut(outputFile);
    if (!fileOut.is_open()) {
        std::cerr << "Error opening output file: "
        << std::filesystem::absolute(outputFile).string() << std::endl;
        return 1;
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
    return 0;
}
