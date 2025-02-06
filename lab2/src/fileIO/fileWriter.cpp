#include "fileWriter.h"
#include "ioExceptions.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <utility>

fileWriter::fileWriter(std::string fname, Universe& u)
    : filename(std::move(fname)), u(u) {}

void fileWriter::saveToFile() const {
    QString QFileName = QString::fromStdString(filename);
    if (!QFileName.endsWith(".life")) QFileName += ".life";
    QFile file(QFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw openFileException(
            "Failed to open file for writing: " + filename);
    }
    QTextStream out(&file);

    out << "#Life 1.06\n";
    out << "#N " << QString::fromStdString(u.getName()) << "\n";
    out << "#R " << QString::fromStdString(u.getRules().getString()) << "\n";

    for (int y = 0; y < u.getHeight(); ++y) {
        for (int x = 0; x < u.getWidth(); ++x) {
            if (u.getCell(x, y)) out << x << " " << y << "\n";
        }
    }
}
