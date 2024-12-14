cmake_minimum_required(VERSION 3.16)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui Test Widgets)
find_package(GTest REQUIRED)

qt_standard_project_setup()

set(SOURCES
        src/game/gameManager.cpp
        src/game/animManager.cpp
        src/game/rules.cpp
        src/game/universe.cpp
        src/gui/mainWindow.cpp
        src/gui/cmdLayout.cpp
        src/gui/settingsLayout.cpp
        src/fileIO/fileReader.cpp
        src/fileIO/fileWriter.cpp
)

set(HEADERS
        src/include/gameManager.h
        src/include/animManager.h
        src/include/rules.h
        src/include/universe.h
        src/include/mainWindow.h
        src/include/cmdLayout.h
        src/include/settingsLayout.h
        src/include/fileReader.h
        src/include/fileWriter.h
        src/include/ioExceptions.h
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(${PROJECT_NAME}
        src/main.cpp
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        src/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Test
        Qt::Widgets
)

enable_testing()

add_executable(test_lab2
        ${SOURCES}
        ${HEADERS}
        tests/test_universe.cpp
        tests/test_rules.cpp
)

target_include_directories(test_lab2 PRIVATE
        src/include
)

target_link_libraries(test_lab2 PRIVATE
        GTest::GTest
        GTest::Main
        Qt::Core
        Qt::Gui
        Qt::Test
        Qt::Widgets
)

add_test(NAME test_lab2 COMMAND test_lab2)
