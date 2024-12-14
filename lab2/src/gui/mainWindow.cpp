#include "mainWindow.h"
#include <QPainter>
#include <algorithm>
#include <utility>

mainWindow::mainWindow(GameManager &gameMgr, AnimationManager &animMgr,
    QWidget *parent): QMainWindow(parent), gMgr(gameMgr), aMgr(animMgr) {
    setWindowTitle("Conway's Game of Life");
    resize(750, 900);

    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QVBoxLayout(central);
    firstWidgetLine = new cmdLayout(gMgr, aMgr, central);
    secondWidgetLine = new settingsLayout(aMgr, central);

    mainLayout->addLayout(firstWidgetLine);
    mainLayout->addLayout(secondWidgetLine);
    mainLayout->addStretch(2);

    connect(&aMgr, &AnimationManager::universeChanged, this,
        QOverload<>::of(&mainWindow::update));

    connect(secondWidgetLine, &settingsLayout::themeToggleRequested, this,
        &mainWindow::toggleTheme);

    connect(firstWidgetLine, &cmdLayout::exitRequested, this,
        &QMainWindow::close);
}

void mainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);
    const Universe &u = gMgr.getUniverse();

    int w = u.getWidth();
    int h = u.getHeight();
    if (w == 0 || h == 0) {
        p.setPen(color1);
        p.setFont(QFont("Arial", 16));
        p.drawText(rect(), Qt::AlignCenter,
            "Please choose file to load universe from");
        return;
    }

    int topOffset = secondWidgetLine->getOffset();

    int availableWidth = width() - 20;
    int availableHeight = height() - topOffset - 20;
    int cellSize = std::min(availableWidth / w, availableHeight / h);

    p.translate(10, topOffset + 10);
    p.setPen(Qt::gray);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            p.setBrush(u.getCell(x, y) ? color1 : color2);
            p.drawRect(x * cellSize, y * cellSize, cellSize, cellSize);
        }
    }

    p.drawText(10, -10,
               QString::fromStdString(u.getName()) + " " +
               QString::fromStdString(u.getRules().getString()) +
               " Iter:" + QString::number(u.getIteration()) +
               " Population:" + QString::number(u.getPopulation()));
}

void mainWindow::toggleTheme() {
    std::swap(color1, color2);
    update();
}
