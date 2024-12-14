#include "gameManager.h"

GameManager::GameManager(Universe& u): universe(u) {}
Universe &GameManager::getUniverse() { return universe; }

void GameManager::tick() { universe.tick(1); }
void GameManager::tick(int n) { universe.tick(n); }
