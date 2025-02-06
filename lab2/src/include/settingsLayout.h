#ifndef LAB2_SRC_INCLUDE_SETTINGSLAYOUT_H_
#define LAB2_SRC_INCLUDE_SETTINGSLAYOUT_H_

#include "gameManager.h"
#include "animManager.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class settingsLayout : public QHBoxLayout {
    Q_OBJECT

 public:
    explicit settingsLayout(AnimationManager &animMgr, QWidget *parent);
    [[nodiscard]] int getOffset() const;

 signals:
    void themeToggleRequested();

 private slots:
    void onSliderMoved(int value) const;

 private:
    AnimationManager &aMgr;
    QWidget *central;

    QVBoxLayout *sliderLayout;
    QSlider *tickIntervalSlider;
    QLabel *sliderLabel;
    const QString sliderInfo = "Current Tick Interval (ms): ";
    QPushButton *toggleThemeButton;
};

#endif  // LAB2_SRC_INCLUDE_SETTINGSLAYOUT_H_
