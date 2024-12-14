#ifndef LAB2_SRC_INCLUDE_CMDLAYOUT_H_
#define LAB2_SRC_INCLUDE_CMDLAYOUT_H_

#include "gameManager.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QStackedWidget>
#include <QPushButton>

#include "animManager.h"

class cmdLayout : public QHBoxLayout {
    Q_OBJECT

 public:
    explicit cmdLayout(GameManager &gameMgr, AnimationManager &animMgr,
        QWidget *parent);

 signals:
    void exitRequested();

 private slots:
    void tickExecutionRequested() const;
    void animSkipRequested() const;
    void loadFromFileRequested() const;
    void saveToFileRequested() const;
    void helpRequested() const;
    void disableWidgets() const;
    void enableWidgets() const;

 private:
    GameManager &gMgr;
    AnimationManager &aMgr;
    QWidget *central;

    QLineEdit *tickCountEdit;
    QIntValidator *validator;
    QStackedWidget *stackedButton;
    QPushButton *executeTicksButton;
    QPushButton *skipAnimButton;
    QPushButton *loadFromFileButton;
    QPushButton *saveToFileButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
};


#endif  // LAB2_SRC_INCLUDE_CMDLAYOUT_H_
