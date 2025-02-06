#ifndef LAB3_SRC_INCLUDE_PROCESSOR_H_
#define LAB3_SRC_INCLUDE_PROCESSOR_H_

#include <string>
#include <vector>

class SoundProcessor {
 public:
    SoundProcessor(std::string configFile, std::string outputFile,
                   std::vector<std::string> &inputFiles);
    void process() const;

 private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
};

#endif  // LAB3_SRC_INCLUDE_PROCESSOR_H_
