#include <gtest/gtest.h>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include "FrequencyParser.h"

std::string read_file(std::ifstream file) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

class FPTestFixture : public ::testing::Test {
 protected:
    std::unique_ptr<FrequencyParser> parser;
    std::unique_ptr<Reader> input_reader;
    std::unique_ptr<CSVWriter> output_writer;

    FPTestFixture() = default;

    void SetUp() override {
        std::ofstream inputFile("test_input.txt");
        inputFile.close();
        remove("test_output.csv");

        try {
            input_reader = std::make_unique<Reader>("test_input.txt");
            output_writer = std::make_unique<CSVWriter>("test_output.csv");
            parser = std::make_unique<FrequencyParser>(
                input_reader.get(), output_writer.get());
        } catch (const std::exception& e) {
            FAIL() << "Exception during object creation: " << e.what();
        }
    }

    void TearDown() override {
        remove("test_input.txt");
        remove("test_output.csv");
    }
};

TEST_F(FPTestFixture, EmptyInput) {
    try {
        parser->parseAndWrite();
    } catch (const std::runtime_error& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());
    std::string expect = "Word,Frequency,Frequency(%)\n";
    EXPECT_EQ(expect, read_file(std::move(outputFile)));
    outputFile.close();
}

TEST_F(FPTestFixture, HelloWorld) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "hello world\nhello";
    inputFile.close();

    try {
        parser->parseAndWrite();
    } catch (const std::runtime_error& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());
    std::string expect = "Word,Frequency,Frequency(%)\n"
                         "hello,2,66.6667\n"
                         "world,1,33.3333\n";
    EXPECT_EQ(expect, read_file(std::move(outputFile)));
    outputFile.close();
}

TEST_F(FPTestFixture, LowerHigherCases) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "lEsEnKa PREVED MEDved LeSeNkA";
    inputFile.close();

    try {
        parser->parseAndWrite();
    } catch (const std::runtime_error& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());
    std::string expect = "Word,Frequency,Frequency(%)\n"
                         "lesenka,2,50\n"
                         "medved,1,25\n"
                         "preved,1,25\n";
    EXPECT_EQ(expect, read_file(std::move(outputFile)));
    outputFile.close();
}

TEST_F(FPTestFixture, AlphabeticSort) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "C A B Z Y X 111 1";
    inputFile.close();

    try {
        parser->parseAndWrite();
    } catch (const std::runtime_error& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());
    std::string expect = "Word,Frequency,Frequency(%)\n"
                         "1,1,12.5\n"
                         "111,1,12.5\n"
                         "a,1,12.5\n"
                         "b,1,12.5\n"
                         "c,1,12.5\n"
                         "x,1,12.5\n"
                         "y,1,12.5\n"
                         "z,1,12.5\n";
    EXPECT_EQ(expect, read_file(std::move(outputFile)));
    outputFile.close();
}

TEST_F(FPTestFixture, DifferentSeparators) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "Bittersweet_you-know]what they->say?"
              << "We=shine and[we]fade+its&always|the way\n"
              << "Bittersweet#[[[]][$you<know>what_they%say,"
              << "I:guess(everything)is^going}to_kill{you~one`day!";
    inputFile.close();

    try {
        parser->parseAndWrite();
    } catch (const std::runtime_error& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }

    std::ifstream outputFile("test_output.csv");
    ASSERT_TRUE(outputFile.is_open());
    std::string expect = "Word,Frequency,Frequency(%)\n"
                         "you,3,9.67742\n"
                         "bittersweet,2,6.45161\n"
                         "know,2,6.45161\n"
                         "say,2,6.45161\n"
                         "they,2,6.45161\n"
                         "we,2,6.45161\n"
                         "what,2,6.45161\n"
                         "always,1,3.22581\n"
                         "and,1,3.22581\n"
                         "day,1,3.22581\n"
                         "everything,1,3.22581\n"
                         "fade,1,3.22581\n"
                         "going,1,3.22581\n"
                         "guess,1,3.22581\n"
                         "i,1,3.22581\n"
                         "is,1,3.22581\n"
                         "its,1,3.22581\n"
                         "kill,1,3.22581\n"
                         "one,1,3.22581\n"
                         "shine,1,3.22581\n"
                         "the,1,3.22581\n"
                         "to,1,3.22581\n"
                         "way,1,3.22581\n";
    EXPECT_EQ(expect, read_file(std::move(outputFile)));
    outputFile.close();
}

TEST(FPTestExceptions, NonExistentInputFile) {
    std::ofstream inputFile("test_input.txt");
    inputFile.close();
    remove("test_output.csv");

    try {
        auto input_reader = std::make_unique<Reader>("fake_test_input.txt");
        auto output_writer = std::make_unique<CSVWriter>("test_output.csv");
        FrequencyParser parser(input_reader.get(), output_writer.get());

        parser.parseAndWrite();
        FAIL() << "Expected runtime error to be thrown";
    } catch (const std::runtime_error& e) {}

    remove("test_input.txt");
    remove("test_output.csv");
}

TEST(FPTestExceptions, FileWriteError) {
    std::ofstream inputFile("test_input.txt");
    inputFile.close();
    remove("test_output.csv");

    try {
        auto input_reader = std::make_unique<Reader>("test_input.txt");
        auto output_writer = std::make_unique<CSVWriter>("/test_output.csv");
        FrequencyParser parser(input_reader.get(), output_writer.get());

        parser.parseAndWrite();
        FAIL() << "Expected runtime error to be thrown";
    } catch (const std::runtime_error& e) {}

    remove("test_input.txt");
    remove("test_output.csv");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
