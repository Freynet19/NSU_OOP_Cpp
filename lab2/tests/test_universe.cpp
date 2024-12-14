#include "gtest/gtest.h"
#include "universe.h"

TEST(UniverseTest, Initialization) {
    Universe u;
    u.init(10, 10, "", Rules("B3/S23"));
    EXPECT_EQ(u.getWidth(), 10);
    EXPECT_EQ(u.getHeight(), 10);
    EXPECT_EQ(u.getIteration(), 0);
    EXPECT_FALSE(u.getCell(0, 0));
}

TEST(UniverseTest, SetAndGetCell) {
    Universe u;
    u.init(10, 10, "", Rules("B3/S23"));
    u.setCell(1, 1, true);
    EXPECT_TRUE(u.getCell(1, 1));
    EXPECT_FALSE(u.getCell(0, 0));
}

TEST(UniverseTest, Tick) {
    Universe u;
    u.init(3, 3, "", Rules("B3/S23"));
    u.setCell(1, 1, true);
    u.tick();
    EXPECT_EQ(u.getIteration(), 1);
}

TEST(UniverseTest, LargeUniverse) {
    Universe u;
    u.init(100, 100, "", Rules("B3/S23"));
    EXPECT_EQ(u.getWidth(), 100);
    EXPECT_EQ(u.getHeight(), 100);
}

TEST(UniverseTest, NeighborsCount) {
    Universe u;
    u.init(3, 3, "", Rules("B3/S23"));
    u.setCell(0, 0, true);
    u.setCell(0, 1, true);
    EXPECT_EQ(u.getNeighborsCount(1, 1), 2);
}

TEST(UniverseTest, EdgeNeighbors) {
    Universe u;
    u.init(3, 3, "", Rules("B3/S23"));
    u.setCell(0, 0, true);
    u.setCell(2, 2, true);
    EXPECT_EQ(u.getNeighborsCount(0, 0), 1);
    EXPECT_EQ(u.getNeighborsCount(2, 2), 1);
}

TEST(UniverseTest, MultipleTicks) {
    Universe u;
    u.init(3, 3, "", Rules("B3/S23"));
    u.setCell(1, 1, true);
    u.tick(5);
    EXPECT_EQ(u.getIteration(), 5);
}

TEST(UniverseTest, EmptyUniverse) {
    Universe u;
    u.init(3, 3, "", Rules("B3/S23"));
    u.tick();
    EXPECT_EQ(u.getIteration(), 1);
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            EXPECT_FALSE(u.getCell(x, y));
        }
    }
}
