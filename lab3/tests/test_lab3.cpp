#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

#include "wavFile.h"
#include "converterFactory.h"
#include "cfgParser.h"
#include "argValidator.h"
#include "processor.h"
#include "exceptions.h"

TEST(ConverterFactoryTest, CreateMuteConverter) {
    ConverterFactory factory({});
    std::istringstream iss("0 10");
    auto converter = factory.createConverter("mute", iss);
    EXPECT_NE(converter, nullptr);
}

TEST(ConverterFactoryTest, CreateEchoConverter) {
    ConverterFactory factory({});
    std::istringstream iss("500 50");
    auto converter = factory.createConverter("echo", iss);
    EXPECT_NE(converter, nullptr);
}

TEST(ConverterFactoryTest, UnknownConverter) {
    ConverterFactory factory({});
    std::istringstream iss("");
    EXPECT_THROW(factory.createConverter("unknown", iss), ConfigError);
}

TEST(ConverterFactoryTest, PrintHelp) {
    ConverterFactory factory({});
    testing::internal::CaptureStdout();
    factory.printHelp();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(ConfigParserTest, ParseValidConfig) {
    std::ofstream configFile("config.txt");
    configFile << "mute 1 3\n";
    configFile << "echo 100 50\n";
    configFile.close();

    ConfigParser parser("config.txt", {});
    auto converters = parser.parseConverters();

    EXPECT_EQ(converters.size(), 2);

    std::remove("config.txt");
}

TEST(ArgValidatorTest, ValidArguments) {
    char arg0[] = "program";
    char arg1[] = "config.txt";
    char arg2[] = "output.wav";
    char arg3[] = "input1.wav";
    char* argv[] = {arg0, arg1, arg2, arg3};

    std::string configFile, outputFile;
    std::vector<std::string> inputFiles;

    EXPECT_NO_THROW(ArgValidator::validateArgs(4, argv,
        configFile, outputFile, inputFiles));
    EXPECT_EQ(configFile, "config.txt");
    EXPECT_EQ(outputFile, "output.wav");
    EXPECT_EQ(inputFiles.size(), 1);
    EXPECT_EQ(inputFiles[0], "input1.wav");
}

TEST(ArgValidatorTest, InvalidArguments) {
    char arg0[] = "program";
    char arg1[] = "config.txt";
    char* argv[] = {arg0, arg1};

    std::string configFile, outputFile;
    std::vector<std::string> inputFiles;

    EXPECT_THROW(ArgValidator::validateArgs(2, argv,
        configFile, outputFile, inputFiles), InvalidArgumentException);
}

TEST(ArgValidatorTest, InvalidFileExtension) {
    char arg0[] = "program";
    char arg1[] = "config.txt";
    char arg2[] = "output.mp3";
    char arg3[] = "input1.wav";
    char* argv[] = {arg0, arg1, arg2, arg3};

    std::string configFile, outputFile;
    std::vector<std::string> inputFiles;

    EXPECT_THROW(ArgValidator::validateArgs(4, argv,
        configFile, outputFile, inputFiles), InvalidArgumentException);
}

TEST(SoundProcessorTest, ProcessInvalidConfig) {
    std::ofstream configFile("invalid_config.txt");
    configFile << "unknown_converter 1 2\n";
    configFile.close();

    std::vector<std::string> inputFiles = {"input1.wav"};

    SoundProcessor processor("invalid_config.txt", "output.wav", inputFiles);
    EXPECT_THROW(processor.process(), ConfigError);

    std::remove("invalid_config.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
