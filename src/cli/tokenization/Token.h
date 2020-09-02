//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_TOKEN_H
#define TODOLIST_TOKEN_H

#include <string>
#include <optional>
#include "Keyword.h"


class Token {

public:
    static Token create(Keyword tp);
    static Token create(Keyword tp, const std::string&);

public:
    Keyword getType();
    std::optional<std::string> getData();

private:
    Token(Keyword, const std::optional<std::string>&);

private:
    Keyword type_;
    std::optional<std::string> data_;
};


#endif //TODOLIST_TOKEN_H
