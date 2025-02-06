#include "cmdLayout.h"
#include "fileReader.h"
#include "fileWriter.h"
#include "ioExceptions.h"
#include <QMessageBox>
#include <QFileDialog>

#include "animManager.h"

cmdLayout::cmdLayout(GameManager &gameMgr, AnimationManager &animMgr,
    QWidget *parent) : gMgr(gameMgr), aMgr(animMgr), central(parent) {
    tickCountEdit = new QLineEdit(central);
    tickCountEdit->setPlaceholderText("1");
    validator = new QIntValidator(1, 9999, tickCountEdit);
    tickCountEdit->setValidator(validator);
    tickCountEdit->setMaximumWidth(50);

    stackedButton = new QStackedWidget(central);
    executeTicksButton = new QPushButton("Execute", stackedButton);
    skipAnimButton = new QPushButton("Skip Anim", stackedButton);
    stackedButton->addWidget(executeTicksButton);
    stackedButton->addWidget(skipAnimButton);
    stackedButton->setCurrentIndex(0);

    loadFromFileButton = new QPushButton("Load from File...", central);
    saveToFileButton = new QPushButton("Save to File...", central);

    helpButton = new QPushButton("Help", central);
    exitButton = new QPushButton("Exit", central);

    this->addWidget(tickCountEdit);
    this->addWidget(stackedButton);
    this->addWidget(loadFromFileButton);
    this->addWidget(saveToFileButton);
    this->addWidget(helpButton);
    this->addWidget(exitButton);

    tickCountEdit->setEnabled(false);
    stackedButton->setEnabled(false);
    saveToFileButton->setEnabled(false);

    connect(executeTicksButton, &QPushButton::clicked, this,
        &cmdLayout::tickExecutionRequested);
    connect(tickCountEdit, &QLineEdit::returnPressed, this,
        &cmdLayout::tickExecutionRequested);

    connect(&aMgr, &AnimationManager::animStarted, this,
        &cmdLayout::disableWidgets);
    connect(&aMgr, &AnimationManager::animFinished, this,
        &cmdLayout::enableWidgets);

    connect(skipAnimButton, &QPushButton::clicked, this,
        &cmdLayout::animSkipRequested);

    connect(loadFromFileButton, &QPushButton::clicked, this,
        &cmdLayout::loadFromFileRequested);
    connect(saveToFileButton, &QPushButton::clicked, this,
        &cmdLayout::saveToFileRequested);

    connect(helpButton, &QPushButton::clicked, this,
        &cmdLayout::helpRequested);
    connect(exitButton, &QPushButton::clicked, this,
        &cmdLayout::exitRequested);
}

void cmdLayout::tickExecutionRequested() const {
    QString ticksLine = tickCountEdit->text();
    aMgr.executeTicks(ticksLine);
}

void cmdLayout::animSkipRequested() const { aMgr.skipAnimation(); }

void cmdLayout::loadFromFileRequested() const {
    QString fileName = QFileDialog::getOpenFileName(
        central,
        "Load Universe from File",
        "../examples/",
        "Life Files (*.life)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(central, "Error", "No file selected.");
        return;
    }

    try {
        fileReader reader(fileName.toStdString(), gMgr.getUniverse());
        reader.loadFromFile();

        if (QString warningsLog = reader.getWarningsLog(); warningsLog != "") {
            QMessageBox::warning(central, "Warning", warningsLog);
        }
        QMessageBox::information(
            central, "Success", "Universe loaded from " + fileName);

        stackedButton->setEnabled(true);
        enableWidgets();
    } catch (const openFileException &e) {
        QMessageBox::warning(central, "Error", e.what());
    } catch (const invalidInputFileFormat &e) {
        QMessageBox::warning(central, "Error", e.what());
    } catch (const std::exception &e) {
        QMessageBox::warning(central, "Error",
            "Unknown error: " + QString(e.what()));
    }
}

void cmdLayout::saveToFileRequested() const {
    QString fileName = QFileDialog::getSaveFileName(
        central,
        "Save Universe to File",
        "",
        "Life Files (*.life)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(central, "Error", "No file selected.");
        return;
    }

    try {
        fileWriter writer(fileName.toStdString(), gMgr.getUniverse());
        writer.saveToFile();
        QMessageBox::information(central, "Success",
            "Universe saved to " + fileName);
    } catch (const openFileException &e) {
        QMessageBox::warning(central, "Error", e.what());
    } catch (const std::exception &e) {
        QMessageBox::warning(central, "Error",
            "Unknown error: " + QString(e.what()));
    }
}

void cmdLayout::helpRequested() const {
    QMessageBox::information(central, "Help", helpText);
}

void cmdLayout::disableWidgets() const {
    tickCountEdit->setEnabled(false);
    stackedButton->setCurrentIndex(1);
    loadFromFileButton->setEnabled(false);
    saveToFileButton->setEnabled(false);
}

void cmdLayout::enableWidgets() const {
    tickCountEdit->setEnabled(true);
    stackedButton->setCurrentIndex(0);
    loadFromFileButton->setEnabled(true);
    saveToFileButton->setEnabled(true);
}
