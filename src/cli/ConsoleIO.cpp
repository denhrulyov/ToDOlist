//
// Created by denis on 20.08.20.
//

#include "ConsoleIO.h"

void ConsoleIO::putLine(const std::string& message) {
    out_ << message << std::endl;
}
std::string ConsoleIO::readWord() {
    clearPrefixSpaces();
    auto buf_iter = buffer_.begin();
    while (buf_iter != buffer_.end() && *buf_iter != ' ') {
        ++buf_iter;
    }
    auto input = std::string(buffer_.begin(), buf_iter);
    buffer_ = std::string(buf_iter, buffer_.end());
    return input;
}

void ConsoleIO::requestInputLine() {
    clear();
    std::string input;
    std::getline(in_, input);
    buffer_ = input;
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

std::string_view ConsoleIO::seeBuffer() {
    return std::string_view(buffer_);
}

ConsoleIO::ConsoleIO(std::istream &in, std::ostream &out) : in_(in), out_(out) {}
