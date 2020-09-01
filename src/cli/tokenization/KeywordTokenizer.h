//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_KEYWORDTOKENIZER_H
#define TODOLIST_KEYWORDTOKENIZER_H

#include "Tokenizer.h"

class KeywordTokenizer : public Tokenizer {

public:
    Token read(ConsoleIO&) override;
    ~KeywordTokenizer() = default;
};


#endif //TODOLIST_KEYWORDTOKENIZER_H
