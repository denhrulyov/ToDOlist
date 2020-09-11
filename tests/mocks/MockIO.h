//
// Created by denis on 09.09.20.
//

#ifndef TODOLIST_MOCKIO_H
#define TODOLIST_MOCKIO_H


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/tokenization/KeywordTokenizer.h"

using ::testing::Return;

class MockIO : public ConsoleIOInterface {

public:
    MockIO() = default;
    MockIO(const std::string& reads) : reads_(reads) {
        ON_CALL(*this, readWord).WillByDefault(Return(reads_));
    }
    MockIO(const std::string& reads, const std::string& writes) : reads_(reads), writes_(writes) {
        ON_CALL(*this, readWord).WillByDefault(Return(reads_));
        EXPECT_CALL(*this, putLine(writes_)).WillRepeatedly(Return());
    }

public:
    MOCK_METHOD(void, putLine, (const std::string&), (override));
    MOCK_METHOD(std::string, readWord, (), (override));
    MOCK_METHOD(std::string, readRestBuffer, (), (override));
    MOCK_METHOD(void, requestInputLine, (), (override));
    MOCK_METHOD(bool, isEmpty, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(std::string_view , seeBuffer, (), (override));

private:
    std::string reads_;
    std::string writes_;
};


#endif //TODOLIST_MOCKIO_H
