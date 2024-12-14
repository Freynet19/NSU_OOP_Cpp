#ifndef LAB2_SRC_INCLUDE_FILEREADER_H_
#define LAB2_SRC_INCLUDE_FILEREADER_H_

#include "gameManager.h"
#include <QString>
#include <string>

class fileReader {
 public:
    explicit fileReader(const std::string& fname, Universe &u);
    void loadFromFile();
    QString getWarningsLog();
 private:
    std::string filename;
    Universe& u;
    QString warningsLog;
};

#endif  // LAB2_SRC_INCLUDE_FILEREADER_H_
