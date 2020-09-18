//
// Created by denis on 10.09.20.
//

#ifndef TODOLIST_MOCKKEYWORDTOKENIZER_H
#define TODOLIST_MOCKKEYWORDTOKENIZER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/tokenization/Tokenizer.h"

class MockKeywordTokenizer : public Tokenizer {

public:
    MOCK_METHOD(Keyword, read, (ConsoleIOInterface&), (override));
};


#endif //TODOLIST_MOCKKEYWORDTOKENIZER_H
