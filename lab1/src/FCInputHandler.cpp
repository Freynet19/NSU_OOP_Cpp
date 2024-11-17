#include "FCInputHandler.h"
#include <iostream>
#include <limits>

int FCInputHandler::getCacheCapacity() {
    while (true) {
        try {
            std::cout << "Please enter the cache capacity" << std::endl;
            std::cout << "0 - exit program, "
                "any number in [1, 1000] - number of elements in cache:" <<
                std::endl;
            const int input = getIntFromCin(0);
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getCacheType() {
    while (true) {
        try {
            std::cout << "Please select the caching method" << std::endl;
            std::cout << "1 - LRU, 2 - LFU, 0 - exit program:" << std::endl;
            const int input = getIntFromCin(1);
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getFibArgument() {
    while (true) {
        try {
            std::cout << "Please enter the argument" << std::endl;
            std::cout << "0 - exit to main menu, "
                "any number in [1, 93] - number in the Fibonacci sequence:"
                << std::endl;
            const int input = getIntFromCin(2);
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getIntFromCin(int argType) {
    int value;
    std::cin >> value;

    // не удалось обработать сразу
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input (non-number)! Try again.");
    }

    // удалось обработать, но остался мусор
    if (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input (non-number)! Try again.");
    }

    bool isValid;
    switch (argType) {
        case 1:  // cache type
            isValid = 0 <= value && value <= 2;
            break;
        case 2:  // fib number
            isValid = 0 <= value && value <= 93;
            break;
        default:  // cache capacity
            isValid = 0 <= value && value <= 1000;
            break;
    }

    if (!isValid) throw std::invalid_argument(
        "Invalid input (invalid number)! Try again.");

    return value;
}
