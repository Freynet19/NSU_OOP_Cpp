#include "universe.h"
#include <string>
#include <vector>
#include <utility>

Universe::Universe(): width(0), height(0),
    rules("B3/S23"), iteration(0), population(0) {}

void Universe::init(int w, int h, const std::string& n, const Rules& r) {
    width = w;
    height = h;
    field.assign(w * h, false);
    name = n;
    rules = r;
    iteration = 0;
    population = 0;
}

const Rules &Universe::getRules() const { return rules; }
std::string Universe::getName() const { return name; }

int Universe::getWidth() const { return width; }
int Universe::getHeight() const { return height; }
int Universe::getIteration() const { return iteration; }
int Universe::getPopulation() const { return population; }

bool Universe::getCell(int x, int y) const { return field[y * width + x]; }
void Universe::setCell(int x, int y, bool alive) {
    population += alive - field[y * width + x];
    field[y * width + x] = alive;
}

int Universe::getNeighborsCount(int x, int y) const {
    static constexpr int dx[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    static constexpr int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = (x + dx[i] + width) % width;
        int ny = (y + dy[i] + height) % height;
        if (getCell(nx, ny))
            count++;
    }
    return count;
}

void Universe::tick(int steps) {
    for (int i = 0; i < steps; ++i) {
        step();
    }
}

void Universe::step() {
    std::vector<bool> newField = field;
    int newPopulation = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int n = getNeighborsCount(x, y);
            bool alive = getCell(x, y);
            bool aliveAfter = rules.shouldLive(alive, n);
            newField[y * width + x] = aliveAfter;
            newPopulation += aliveAfter;
        }
    }
    field = std::move(newField);
    population = newPopulation;
    iteration++;
}
