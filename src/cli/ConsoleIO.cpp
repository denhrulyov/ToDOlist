//
// Created by denis on 20.08.20.
//

#include "ConsoleIO.h"

void ConsoleIO::log(const std::string& message) {
    std::cout << message << std::endl;
}
std::string ConsoleIO::read() {
    clearPrefixSpaces();
    auto buf_iter = buffer_.begin();
    while (buf_iter != buffer_.end() && *buf_iter != ' ') {
        ++buf_iter;
    }
    auto input = std::string(buffer_.begin(), buf_iter);
    if (input.empty()) {
        std::getline(std::cin, buffer_);
        input = read();
    } else {
        buffer_ = std::string(buf_iter, buffer_.end());
    }
    return input;
}

std::string ConsoleIO::readLine() {
    clear();
    std::string input;
    std:getline(std::cin, input);
    return input;
}

void ConsoleIO::clear() {
    buffer_.clear();
}

bool ConsoleIO::isEmpty() {
    clearPrefixSpaces();
    return buffer_.empty();
}

std::string ConsoleIO::readRestBuffer() {
    clearPrefixSpaces();
    auto input = buffer_;
    clear();
    return input;
}

void ConsoleIO::clearPrefixSpaces() {
    auto buf_iter = buffer_.begin();
    while (buf_iter != buffer_.end() && *buf_iter == ' ') {
        ++buf_iter;
    }
    buffer_ = std::string(buf_iter, buffer_.end());
}
