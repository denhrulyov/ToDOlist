//
// Created by denis on 31.08.20.
//

#include "MultiwordDataTokenizer.h"
#include "cli/ConsoleIO.h"
#include <map>

Token MultiwordDataTokenizer::read(ConsoleIO &io) {
    std::string input = io.readRestBuffer();
    return Token::create(TypeToken::UNKNOWN, input);
}
