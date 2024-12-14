#include "animManager.h"

AnimationManager::AnimationManager(GameManager &gameMgr)
    : gMgr(gameMgr), remainingTicks(0) {
    animationTimer.setInterval(static_cast<int>(tickInterval::DEFAULT));
    connect(&animationTimer, &QTimer::timeout, this,
        &AnimationManager::performSingleTick);
}

// когда двигаем ползунок
void AnimationManager::setTickInterval(int ms) {
    animationTimer.setInterval(ms);
}

// когда жмем execute введя или не введя кол-во тиков
void AnimationManager::executeTicks(QString ticksStr) {
    if (ticksStr.isEmpty()) ticksStr = "1";
    int tickValue = ticksStr.toInt();

    if (tickValue == 1) gMgr.tick();
    else startAnimation(tickValue);
    emit universeChanged();
}

// запускает таймер который сам будет вызывать тики
void AnimationManager::startAnimation(int steps) {
    remainingTicks = steps;
    animationTimer.start();
    emit animStarted();
}

// когда жмем skip anim
void AnimationManager::skipAnimation() {
    if (remainingTicks > 0) {
        gMgr.tick(remainingTicks);
        remainingTicks = 0;
    }
    animationTimer.stop();
    emit universeChanged();
    emit animFinished();
}

// то что вызывается таймером раз в X тиков
void AnimationManager::performSingleTick() {
    if (remainingTicks > 0) {
        gMgr.tick();
        remainingTicks--;
        emit universeChanged();
    } else {
        animationTimer.stop();
        emit animFinished();
    }
}
