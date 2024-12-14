#ifndef LAB2_SRC_INCLUDE_ANIMMANAGER_H_
#define LAB2_SRC_INCLUDE_ANIMMANAGER_H_

#include "gameManager.h"
#include <QTimer>

enum class tickInterval : int {
    DEFAULT = 500,
    MIN = 50,
    MAX = 1000,
    STEP = 50
};

class AnimationManager : public QObject {
    Q_OBJECT

 public:
    explicit AnimationManager(GameManager &gameMgr);

    void setTickInterval(int ms);

    void executeTicks(QString ticksStr);
    void startAnimation(int steps);
    void skipAnimation();

 signals:
    void universeChanged();
    void animStarted();
    void animFinished();

 private slots:
    void performSingleTick();

 private:
    GameManager &gMgr;
    QTimer animationTimer;
    int remainingTicks;
};

#endif  // LAB2_SRC_INCLUDE_ANIMMANAGER_H_
