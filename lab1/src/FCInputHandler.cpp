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
            const int input = getIntFromCin(FCInputType::CACHE_CAPACITY);
            return input;
        } catch (const std::invalid_argument& e) {  // add custom exception
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
            const int input = getIntFromCin(FCInputType::CACHE_TYPE);
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
            const int input = getIntFromCin(FCInputType::FIB_NUMBER);
            return input;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getIntFromCin(FCInputType argType) {
    int value;
    std::cin >> value;

    // не удалось обработать сразу
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("invalid input (non-number)! Try again.");
    }

    // удалось обработать, но остался мусор
    if (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("invalid input (non-number)! Try again.");
    } // ошибки с маленькой буквы

    bool isValid = false;
    switch (argType) {
    case FCInputType::CACHE_CAPACITY:
        isValid = 0 <= value && value <= maxCapValue; // объяснить константы в классе
        break;
    case FCInputType::CACHE_TYPE:
        isValid = 0 <= value && value <= maxTypeValue;
        break;
    case FCInputType::FIB_NUMBER:
        isValid = 0 <= value && value <= maxFibValue;
        break;
    }

    if (!isValid) throw std::invalid_argument(
        "Invalid input (invalid number)! Try again.");

    return value;
}
