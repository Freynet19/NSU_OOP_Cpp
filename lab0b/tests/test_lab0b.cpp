#include <gtest/gtest.h>
#include "FrequencyParser.h"
#include <fstream>

class FPTestFixture : public ::testing::Test {
 protected:
    void SetUp() override {
        std::ofstream inputFile("test_input.txt");
        inputFile.close();
        remove("test_output.csv");
    }

    void TearDown() override {
        remove("test_input.txt");
        remove("test_output.csv");
    }
};

/*TEST_F(FPTestFixture, TEMPLATE) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "ENTER TEXT HERE";
    inputFile.close();

    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}*/

TEST_F(FPTestFixture, EmptyInput) {
    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}

TEST_F(FPTestFixture, HelloWorld) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "hello world\nhello";
    inputFile.close();

    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "hello,2,66.6667");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "world,1,33.3333");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}

TEST_F(FPTestFixture, LowerHigherCases) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "lEsEnKa PREVED MEDved LeSeNkA";
    inputFile.close();

    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "lesenka,2,50");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "medved,1,25");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "preved,1,25");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}

TEST_F(FPTestFixture, AlphabeticSort) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "C A B Z Y X 111 1";
    inputFile.close();

    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "1,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "111,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "a,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "b,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "c,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "x,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "y,1,12.5");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "z,1,12.5");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}

TEST_F(FPTestFixture, DifferentSeparators) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "Bittersweet_you-know]what they->say?"
        << "We=shine and[we]fade+its&always|the way\n"
        << "Bittersweet#[[[]][$you<know>what_they%say,"
        << "I:guess(everything)is^going}to_kill{you~one`day!";
    inputFile.close();

    FrequencyParser parser("test_input.txt", "test_output.csv");
    EXPECT_EQ(parser.GetWordFrequency(), 0);

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    EXPECT_EQ(line, "Word,Frequency,Frequency(%)");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "you,3,9.67742");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "bittersweet,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "know,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "say,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "they,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "we,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "what,2,6.45161");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "always,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "and,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "day,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "everything,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "fade,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "going,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "guess,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "i,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "is,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "its,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "kill,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "one,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "shine,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "the,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "to,1,3.22581");
    std::getline(outputFile, line);
    EXPECT_EQ(line, "way,1,3.22581");
    EXPECT_FALSE(std::getline(outputFile, line));

    outputFile.close();
}

TEST_F(FPTestFixture, NonExistentInputFile) {
    FrequencyParser parser("fake_test_input.txt", "test_output.csv");
    EXPECT_NE(parser.GetWordFrequency(), 0);
}

TEST_F(FPTestFixture, FileWriteError) {
    FrequencyParser parser("test_input.txt", "/test_output.csv");
    EXPECT_NE(parser.GetWordFrequency(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
