#include "fileReader.h"
#include "ioExceptions.h"
#include <QFile>
#include <QTextStream>
#include <set>
#include <string>
#include <algorithm>
#include <utility>

fileReader::fileReader(std::string fname, Universe& u)
    : filename(std::move(fname)), u(u), warningsLog("") {}

void fileReader::loadFromFile() {
    QString QFileName = QString::fromStdString(filename);
    if (!QFileName.endsWith(".life")) QFileName += ".life";
    QFile file(QFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw openFileException(
            "Failed to open file for reading: " + filename);
    }
    QTextStream in(&file);

    if (QString firstLine = in.readLine(); firstLine != "#Life 1.06") {
        throw invalidInputFileFormat();
    }

    std::string uname = parseLineToName(in);
    Rules rules = parseLineToRules(in);

    std::set<std::pair<int, int>> aliveCells;
    // unordered_set не используется т.к не имеет хэш-функции для pair<int, int>
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        parseLineToCell(line, aliveCells);
    }

    int width, height, minX, minY;
    calculateFieldSize(width, height, minX, minY, aliveCells);

    u.init(width, height, uname, rules);
    for (const auto & [fst, snd] : aliveCells) {
        int x = fst - minX;
        int y = snd - minY;
        u.setCell(x, y, true);
    }
}

QString fileReader::getWarningsLog() { return warningsLog; }

std::string fileReader::parseLineToName(QTextStream& in) {
    qint64 prevLine = in.pos();
    QString uNameLine = in.readLine();
    if (!uNameLine.startsWith("#N ")) {
        warningsLog += "Missing universe name. Using default name.\n";
        in.seek(prevLine);
        return "Unnamed Universe";
    }
    return uNameLine.mid(3).toStdString();
}

Rules fileReader::parseLineToRules(QTextStream &in) {
    qint64 prevLine = in.pos();
    Rules defaultRules("B3/S23");
    QString rulesLine = in.readLine();
    if (!rulesLine.startsWith("#R ")) {
        warningsLog += "Missing rules. Using default rules.\n";
        in.seek(prevLine);
        return defaultRules;
    }
    try {
        QString rulesStr = rulesLine.mid(3);
        return Rules(rulesStr.toStdString());
    } catch (const ruleParsingException &e) {
        warningsLog += "Invalid rules format: " +
            QString(e.what()) + "\nUsing default rules.\n";
        return defaultRules;
    }
}


void fileReader::parseLineToCell(
    const QString& line, std::set<std::pair<int, int>>& aliveCells) {
    if (line.isEmpty() || line.startsWith("#")) return;

    QStringList parts = line.split(" ");
    if (parts.size() != 2) {
        warningsLog += "Invalid coordinate format. "
            "Skipping line: " + QString(line) + "\n";
        return;
    }

    bool xOk, yOk;
    int x = parts[0].toInt(&xOk);
    int y = parts[1].toInt(&yOk);
    if (!xOk || !yOk) {
        warningsLog += "Invalid coordinate values. "
            "Skipping line: " + QString(line) + "\n";
        return;
    }

    if (aliveCells.contains({x, y})) {
        warningsLog += "Duplicate coordinates. "
            "Skipping line: " + QString(line) + "\n";
        return;
    }

    aliveCells.insert({x, y});
}

void fileReader::calculateFieldSize(
    int &width, int &height, int &minX, int &minY,
    const std::set<std::pair<int, int>> &aliveCells) {
    minX = 0, minY = 0;
    int maxX = 0, maxY = 0;
    for (const auto &[fst, snd] : aliveCells) {
        int x = fst;
        int y = snd;
        minX = std::min(x, minX);
        maxX = std::max(x, maxX);
        minY = std::min(y, minY);
        maxY = std::max(y, maxY);
    }

    width = maxX - minX + 1;
    height = maxY - minY + 1;

    constexpr int minWidth = static_cast<int>(minFieldSize::WIDTH);
    constexpr int minHeight = static_cast<int>(minFieldSize::HEIGHT);

    if (width < minWidth) {
        int offsetX = (minWidth - width) / 2;
        minX -= offsetX;
        width = minWidth;
    }
    if (height < minHeight) {
        int offsetY = (minHeight - height) / 2;
        minY -= offsetY;
        height = minHeight;
    }
}
