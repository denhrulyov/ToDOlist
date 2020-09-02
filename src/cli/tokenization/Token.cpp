//
// Created by denis on 31.08.20.
//

#include "Token.h"

Token Token::create(Keyword tp) {
    return Token(tp, std::nullopt);
}

Token Token::create(Keyword tp, const std::string &data) {
    return Token(tp, data);
}

Token::Token(Keyword tp, const std::optional<std::string> &data)
:
type_(tp),
data_(data)
{}

Keyword Token::getType() {
    return type_;
}

std::optional<std::string> Token::getData() {
    return data_;
}

