cmake_minimum_required(VERSION 3.29)
project(lab0b)
set(TEST_NAME test_lab0b)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

set(SRC
        src/Reader.cpp
        src/FrequencyParser.cpp
        src/Writer.cpp
)

set(INCLUDE_DIRS
        src/include
)

add_executable(${PROJECT_NAME} src/main.cpp ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

add_executable(${TEST_NAME} tests/test_lab0b.cpp ${SRC})
target_include_directories(${TEST_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main)

add_test(NAME gtests_lab0b COMMAND ${TEST_NAME})
