#include "FCInputHandler.h"

#include <iostream>
#include <limits>
#include "FibonacciCached.h"
#include "InputValidators.h"

#include "UnprocessableArg.h"
#include "InvalidCapArg.h"
#include "InvalidTypeArg.h"
#include "InvalidFibArg.h"

int FCInputHandler::getCacheCapacity() {
    while (true) {
        try {
            std::cout << "Please enter the cache capacity" << std::endl;
            std::cout << "0 - exit program, "
                "any number in [1, 1000] - number of elements in cache:" <<
                std::endl;
            return getIntFromCin(FCArgumentType::CACHE_CAPACITY);
        } catch (const InvalidCapacityArgumentException& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        } catch (const UnprocessableArgumentException& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
        }
    }
}

СacheType FCInputHandler::getCacheType() {
    while (true) {
        try {
            std::cout << "Please select the caching method" << std::endl;
            std::cout << "1 - LRU, 2 - LFU, 0 - exit program:" << std::endl;
            return static_cast<СacheType>(
                getIntFromCin(FCArgumentType::CACHE_TYPE));
        } catch (const InvalidTypeArgumentException& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        } catch (const UnprocessableArgumentException& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            return getIntFromCin(FCArgumentType::FIB_NUMBER);
        } catch (const InvalidFibNumberArgumentException& e) {
            std::cin.clear();
            std::cout << e.what() << std::endl;
        } catch (const UnprocessableArgumentException& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
        }
    }
}

int FCInputHandler::getIntFromCin(FCArgumentType argType) {
    int value;
    std::cin >> value;

    if (std::cin.fail()) {
        throw UnprocessableArgumentException(
            "invalid input: garbage at the beginning! Try again.");
    }

    if (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        throw UnprocessableArgumentException(
            "invalid input: garbage at the end! Try again.");
    }

    ProgramArgumentsValidator validator(value, argType);
    validator.validate();

    return value;
}
