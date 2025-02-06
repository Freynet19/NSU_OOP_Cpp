#ifndef LAB2_SRC_INCLUDE_MAINWINDOW_H_
#define LAB2_SRC_INCLUDE_MAINWINDOW_H_

#include "cmdLayout.h"
#include "settingsLayout.h"
#include <QMainWindow>

class mainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit mainWindow(GameManager &gameMgr, AnimationManager &animMgr,
       QWidget *parent = nullptr);

 protected:
    void paintEvent(QPaintEvent *) override;

 signals:
    void waitingForUniverse();
    void gotUniverse();

 private slots:
    void toggleTheme();

 private:
    GameManager &gMgr;
    AnimationManager &aMgr;
    QWidget *central;

    QVBoxLayout *mainLayout;
    cmdLayout *firstWidgetLine;
    settingsLayout *secondWidgetLine;

    Qt::GlobalColor color1 = Qt::white;
    Qt::GlobalColor color2 = Qt::black;
};

#endif  // LAB2_SRC_INCLUDE_MAINWINDOW_H_
