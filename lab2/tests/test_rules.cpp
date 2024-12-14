#include "gtest/gtest.h"
#include "rules.h"
#include "ioExceptions.h"

TEST(RulesTest, Parsing) {
    Rules r("B3/S23");
    EXPECT_EQ(r.getString(), "B3/S23");
}

TEST(RulesTest, ShouldLive) {
    Rules r("B3/S23");
    EXPECT_TRUE(r.shouldLive(true, 2));
    EXPECT_FALSE(r.shouldLive(true, 1));
    EXPECT_TRUE(r.shouldLive(false, 3));
    EXPECT_FALSE(r.shouldLive(false, 2));
}

TEST(RulesTest, ComplexRules) {
    Rules r("B36/S23");
    EXPECT_TRUE(r.shouldLive(false, 3));
    EXPECT_TRUE(r.shouldLive(false, 6));
    EXPECT_FALSE(r.shouldLive(false, 2));
}

TEST(RulesTest, InvalidRules) {
    EXPECT_THROW(Rules("B3/S2A"), ruleParsingException);
    EXPECT_THROW(Rules("B3S23"), ruleParsingException);
    EXPECT_THROW(Rules("B3/"), ruleParsingException);
}

TEST(RulesTest, EdgeCases) {
    Rules r("B3/S23");
    EXPECT_FALSE(r.shouldLive(true, 0));
    EXPECT_FALSE(r.shouldLive(true, 4));
}

TEST(RulesTest, BirthOnly) {
    Rules r("B3/S");
    EXPECT_TRUE(r.shouldLive(false, 3));
    EXPECT_FALSE(r.shouldLive(false, 2));
}

TEST(RulesTest, SurviveOnly) {
    Rules r("B/S23");
    EXPECT_TRUE(r.shouldLive(true, 2));
    EXPECT_FALSE(r.shouldLive(true, 1));
}

TEST(RulesTest, NoRules) {
    Rules r("B/S");
    EXPECT_FALSE(r.shouldLive(true, 2));
    EXPECT_FALSE(r.shouldLive(false, 3));
}

TEST(RulesTest, AllBirth) {
    Rules r("B012345678/S");
    for (int i = 0; i <= 8; ++i) {
        EXPECT_TRUE(r.shouldLive(false, i));
    }
}

TEST(RulesTest, AllSurvive) {
    Rules r("B/S012345678");
    for (int i = 0; i <= 8; ++i) {
        EXPECT_TRUE(r.shouldLive(true, i));
    }
}
