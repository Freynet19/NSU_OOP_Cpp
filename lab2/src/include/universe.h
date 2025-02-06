#ifndef LAB2_SRC_INCLUDE_UNIVERSE_H_
#define LAB2_SRC_INCLUDE_UNIVERSE_H_

#include <vector>
#include <string>
#include "rules.h"

class Universe {
 public:
    Universe();
    void init(int w, int h, const std::string& n, const Rules& r);

    [[nodiscard]] const Rules &getRules() const;
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getIteration() const;
    [[nodiscard]] int getPopulation() const;
    [[nodiscard]] int getNeighborsCount(int x, int y) const;
    [[nodiscard]] bool getCell(int x, int y) const;
    void setCell(int x, int y, bool alive);

    void tick(int steps = 1);

 private:
    void step();

    int width;
    int height;
    std::vector<bool> field;
    std::string name;
    Rules rules;
    int iteration;
    int population;
};

#endif  // LAB2_SRC_INCLUDE_UNIVERSE_H_
