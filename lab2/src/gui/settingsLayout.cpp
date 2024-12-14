#include "settingsLayout.h"

settingsLayout::settingsLayout(AnimationManager &animMgr, QWidget* parent)
        : aMgr(animMgr), central(parent) {
    tickIntervalSlider = new QSlider(Qt::Horizontal, central);
    tickIntervalSlider->setMinimum(static_cast<int>(tickInterval::MIN));
    tickIntervalSlider->setMaximum(static_cast<int>(tickInterval::MAX));
    tickIntervalSlider->setValue(static_cast<int>(tickInterval::DEFAULT));
    tickIntervalSlider->setSingleStep(static_cast<int>(tickInterval::STEP));
    sliderLabel = new QLabel(sliderInfo +
        QString::number(static_cast<int>(tickInterval::DEFAULT)), central);
    sliderLabel->setAlignment(Qt::AlignCenter);

    sliderLayout = new QVBoxLayout();
    sliderLayout->addWidget(tickIntervalSlider);
    sliderLayout->addWidget(sliderLabel);

    toggleThemeButton = new QPushButton("Toggle Theme", central);

    this->addLayout(sliderLayout);
    this->addWidget(toggleThemeButton);

    connect(tickIntervalSlider, &QSlider::valueChanged, this,
        &settingsLayout::onSliderMoved);
    connect(toggleThemeButton, &QPushButton::clicked, this,
        &settingsLayout::themeToggleRequested);
}

int settingsLayout::getOffset() const {
    return sliderLabel->geometry().bottom() + 20;
}

void settingsLayout::onSliderMoved(const int value) const {
    sliderLabel->setText(sliderInfo + QString::number(value));
    aMgr.setTickInterval(value);
}
