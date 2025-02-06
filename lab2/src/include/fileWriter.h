#ifndef LAB2_SRC_INCLUDE_FILEWRITER_H_
#define LAB2_SRC_INCLUDE_FILEWRITER_H_

#include "gameManager.h"
#include <string>

class fileWriter {
 public:
    explicit fileWriter(std::string fname, Universe &u);
    void saveToFile() const;
 private:
    std::string filename;
    Universe& u;
};

#endif  // LAB2_SRC_INCLUDE_FILEWRITER_H_
