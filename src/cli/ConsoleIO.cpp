//
// Created by denis on 20.08.20.
//

#include "ConsoleIO.h"

void ConsoleIO::log(const std::string& message) {
    std::cout << message << std::endl;
}
std::string ConsoleIO::read() {
    std::cin.clear();
    std::string input;
    std::cin >> input;
    return input;
}