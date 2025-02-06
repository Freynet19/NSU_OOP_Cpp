#include <QApplication>
#include "universe.h"
#include "gameManager.h"
#include "animManager.h"
#include "mainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Universe u;
    GameManager gMgr(u);
    AnimationManager aMgr(gMgr);

    mainWindow w(gMgr, aMgr);
    w.show();
    return app.exec();
}
