#ifndef LAB2_SRC_INCLUDE_GAMEMANAGER_H_
#define LAB2_SRC_INCLUDE_GAMEMANAGER_H_

#include "universe.h"

enum class minFieldSize : int {
    WIDTH = 32,
    HEIGHT = 32
};

class GameManager {
 public:
    explicit GameManager(Universe& u);
    Universe &getUniverse();

    void tick();
    void tick(int n);

 private:
    Universe universe;
};

#endif  // LAB2_SRC_INCLUDE_GAMEMANAGER_H_
