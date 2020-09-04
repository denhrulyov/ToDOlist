//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_TOKENIZER_H
#define TODOLIST_TOKENIZER_H

#include <cli/ConsoleIOInterface.h>
#include "Keyword.h"

class Tokenizer {

public:
    virtual Keyword  read(ConsoleIOInterface &) = 0;
    virtual ~Tokenizer() = default;
};


#endif //TODOLIST_TOKENIZER_H
