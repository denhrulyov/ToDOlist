//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_MULTIWORDDATATOKENIZERINTERFACE_H
#define TODOLIST_MULTIWORDDATATOKENIZERINTERFACE_H

#include "Tokenizer.h"

class MultiwordDataTokenizerInterface : public Tokenizer {

public:
    virtual Token read(ConsoleIO&) = 0;
    virtual ~MultiwordDataTokenizerInterface() = default;
};



#endif //TODOLIST_MULTIWORDDATATOKENIZERINTERFACE_H
