#include "fileReader.h"
#include "ioExceptions.h"
#include <QFile>
#include <QTextStream>
#include <set>
#include <string>
#include <algorithm>

fileReader::fileReader(const std::string& fname, Universe& u)
    : filename(fname), u(u), warningsLog("") {}

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

    qint64 prevLine = in.pos();
    std::string uname = "Unnamed Universe";
    if (QString uNameLine = in.readLine();
        uNameLine.startsWith("#N ")) {
        uname = uNameLine.mid(3).toStdString();
    } else {
        warningsLog += "Missing universe name. Using default name.\n";
        in.seek(prevLine);
    }

    prevLine = in.pos();
    Rules rules("B3/S23");
    if (QString rulesLine = in.readLine(); rulesLine.startsWith("#R ")) {
        QString rulesStr = rulesLine.mid(3);
        try {
            rules = Rules(rulesStr.toStdString());
        } catch (const ruleParsingException &e) {
            warningsLog += "Invalid rules format: " +
                QString(e.what()) + "\nUsing default rules.\n";
        }
    } else {
        warningsLog += "Missing rules. Using default rules.\n";
        in.seek(prevLine);
    }

    std::set<std::pair<int, int>> aliveCells;
    // unordered_set не используется т.к не имеет хэш-функции для pair<int, int>
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("#")) continue;

        QStringList parts = line.split(" ");
        if (parts.size() != 2) {
            warningsLog += "Invalid coordinate format. "
                "Skipping line: " + QString(line) + "\n";
            continue;
        }

        bool xOk, yOk;
        int x = parts[0].toInt(&xOk);
        int y = parts[1].toInt(&yOk);
        if (!xOk || !yOk) {
            warningsLog += "Invalid coordinate values. "
                "Skipping line: " + QString(line) + "\n";
            continue;
        }

        if (aliveCells.contains({x, y})) {
            warningsLog += "Duplicate coordinates. "
                "Skipping line: " + QString(line) + "\n";
            continue;
        }

        aliveCells.insert({x, y});
    }

    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    for (const auto &[fst, snd] : aliveCells) {
        int x = fst;
        int y = snd;
        minX = std::min(x, minX);
        maxX = std::max(x, maxX);
        minY = std::min(y, minY);
        maxY = std::max(y, maxY);
    }

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    constexpr int minWidth = static_cast<int>(minFieldSize::WIDTH);
    constexpr int minHeight = static_cast<int>(minFieldSize::HEIGHT);

    if (width < minWidth) {
        int offsetX = (minWidth - width) / 2;
        minX -= offsetX;
        maxX += (minWidth - width) - offsetX;
        width = minWidth;
    }
    if (height < minHeight) {
        int offsetY = (minHeight - height) / 2;
        minY -= offsetY;
        maxY += (minHeight - height) - offsetY;
        height = minHeight;
    }

    u.init(width, height, uname, rules);
    for (const auto & [fst, snd] : aliveCells) {
        int x = fst - minX;
        int y = snd - minY;
        u.setCell(x, y, true);
    }
}

QString fileReader::getWarningsLog() { return warningsLog; }
