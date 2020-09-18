//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_KEYWORDTOKENIZER_H
#define TODOLIST_KEYWORDTOKENIZER_H

#include "Keyword.h"
#include "Tokenizer.h"

class KeywordTokenizer : public Tokenizer {

public:
    Keyword  read(ConsoleIOInterface &) override;
    virtual ~KeywordTokenizer() = default;
};


#endif //TODOLIST_KEYWORDTOKENIZER_H
