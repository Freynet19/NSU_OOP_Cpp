#ifndef LAB2_SRC_INCLUDE_FILEREADER_H_
#define LAB2_SRC_INCLUDE_FILEREADER_H_

#include "gameManager.h"
#include <QString>
#include <QTextStream>
#include <string>
#include <set>

class fileReader {
 public:
    explicit fileReader(std::string fname, Universe &u);
    void loadFromFile();
    QString getWarningsLog();
 private:
    std::string parseLineToName(QTextStream &in);
    Rules parseLineToRules(QTextStream &in);
    void parseLineToCell(const QString &line,
        std::set<std::pair<int, int>>& aliveCells);
    static void calculateFieldSize(int &width, int &height,
        int &minX, int &minY, const std::set<std::pair<int, int>>& aliveCells);

    std::string filename;
    Universe& u;
    QString warningsLog;
};

#endif  // LAB2_SRC_INCLUDE_FILEREADER_H_
