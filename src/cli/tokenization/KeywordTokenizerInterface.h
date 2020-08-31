//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_KEYWORDTOKENIZERINTERFACE_H
#define TODOLIST_KEYWORDTOKENIZERINTERFACE_H

#include "Tokenizer.h"

class KeywordTokenizerInterface : public Tokenizer {

public:
    virtual Token read(ConsoleIO&) = 0;
    virtual ~KeywordTokenizerInterface() = default;
};


#endif //TODOLIST_KEYWORDTOKENIZERINTERFACE_H
