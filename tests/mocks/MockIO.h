//
// Created by denis on 09.09.20.
//

#ifndef TODOLIST_MOCKIO_H
#define TODOLIST_MOCKIO_H


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/tokenization/KeywordTokenizer.h"

class MockIO : public ConsoleIOInterface {

public:
    MOCK_METHOD(void, putLine, (const std::string&), (override));
    MOCK_METHOD(std::string, readWord, (), (override));
    MOCK_METHOD(std::string, readRestBuffer, (), (override));
    MOCK_METHOD(void, requestInputLine, (), (override));
    MOCK_METHOD(bool, isEmpty, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(std::string_view , seeBuffer, (), (override));

private:
    std::string gives_;
};


#endif //TODOLIST_MOCKIO_H
