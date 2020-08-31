//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_TOKEN_H
#define TODOLIST_TOKEN_H

#include <string>
#include <optional>
#include "TypeToken.h"


class Token {

public:
    static Token create(TypeToken tp);
    static Token create(TypeToken tp, const std::string&);

public:
    TypeToken getType();
    std::optional<std::string> getData();

private:
    Token(TypeToken, const std::optional<std::string>&);

private:
    TypeToken type_;
    std::optional<std::string> data_;
};


#endif //TODOLIST_TOKEN_H
