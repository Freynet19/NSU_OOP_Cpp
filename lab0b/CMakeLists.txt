cmake_minimum_required(VERSION 3.29)
project(lab0b)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

set(SRC
        src/main.cpp
        src/Reader.cpp
        src/FrequencyParser.cpp
        src/Writer.cpp
)

set(TEST_SRC
        tests/test_lab0b.cpp
        src/Reader.cpp
        src/FrequencyParser.cpp
        src/Writer.cpp
)

set(INCLUDE_DIRS
        src/include
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

add_executable(test_lab0b ${TEST_SRC})
target_include_directories(test_lab0b PRIVATE ${INCLUDE_DIRS})
target_link_libraries(test_lab0b PRIVATE GTest::GTest GTest::Main)

add_test(NAME gtests_lab0b COMMAND test_lab0b)
