//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_KEYWORDTOKENIZER_H
#define TODOLIST_KEYWORDTOKENIZER_H

#include "KeywordTokenizerInterface.h"

class KeywordTokenizer : public KeywordTokenizerInterface {

public:
    Token read(ConsoleIO&) override;
    ~KeywordTokenizer() = default;
};


#endif //TODOLIST_KEYWORDTOKENIZER_H
