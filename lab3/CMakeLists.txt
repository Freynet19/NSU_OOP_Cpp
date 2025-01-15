cmake_minimum_required(VERSION 3.29)
project(lab3)
set(TEST_NAME test_lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

set(SRC
        src/processor.cpp
        src/cfgParser.cpp
        src/wavFile.cpp
        src/converterFactory.cpp
        src/argValidator.cpp
        src/converters/muteConverter.cpp
        src/converters/mixConverter.cpp
        src/converters/echoConverter.cpp
        src/converters/reverseConverter.cpp
)

set(INCLUDE_DIRS
        src/include
        src/converters/include
)

add_executable(${PROJECT_NAME} src/main.cpp ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

add_executable(${TEST_NAME} tests/test_lab3.cpp ${SRC})
target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
