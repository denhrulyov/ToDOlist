//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_TOKENIZER_H
#define TODOLIST_TOKENIZER_H

#include "Keyword.h"
class ConsoleIO;

class Tokenizer {

public:
    virtual Keyword  read(ConsoleIO&) = 0;
    virtual ~Tokenizer() = default;
};


#endif //TODOLIST_TOKENIZER_H