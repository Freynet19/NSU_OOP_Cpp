#include "FCInputHandler.h"
#include <iostream>
#include <limits>

int FCInputHandler::getCacheCapacity() {
    while (true) {
        try {
            std::cout << "Please enter the cache capacity" << std::endl;
            std::cout << "0 - exit program, "
                "any number above - number of elements in cache:" << std::endl;
            int input;
            std::cin >> input;
            if (std::cin.fail() || input < 0) {
                throw std::invalid_argument("Invalid input! Try again.");
            }
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // удаление оставшихся символов

            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getCacheType() {
    while (true) {
        try {
            std::cout << "Please select the caching method" << std::endl;
            std::cout << "1 - LRU, 2 - LFU, 0 - exit program:" << std::endl;
            int input;
            std::cin >> input;
            if (std::cin.fail() || input < 0 || input > 2) {
                throw std::invalid_argument("Invalid input! Try again.");
            }
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getArgument() {
    while (true) {
        try {
            std::cout << "Please enter the argument" << std::endl;
            std::cout << "0 - exit to main menu, "
                "any number above - number in the Fibonacci sequence:"
                << std::endl;
            int input;
            std::cin >> input;
            if (std::cin.fail() || input < 0) {
                throw std::invalid_argument("Invalid input! Try again.");
            }
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}
