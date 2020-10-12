//
// Created by denis on 05.10.20.
//

#include "cli/state_machines/main/states/SaveToFileState.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockService.h"

using ::testing::ReturnRef;

class SaveToFileTest : public ::testing::Test {

};

TEST_F(SaveToFileTest, TestSwitchParseCommand) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    testing::NiceMock<MockContext> mctx;
    MockService ms;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getTaskService).WillOnce(ReturnRef(ms));
    testing::NiceMock<MockIO> mio;
    EXPECT_CALL(mio, readRestBuffer).WillOnce(Return("abacabadabacaba"));
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(ms, saveToFile).WillOnce(Return(RequestResult::success()));
    SaveToFileState state;
    state.execute(mctx, mf);
}

TEST_F(SaveToFileTest, TestSwitchParseCommandOnBad) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    testing::NiceMock<MockContext> mctx;
    MockService ms;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getTaskService).WillOnce(ReturnRef(ms));
    testing::NiceMock<MockIO> mio;
    EXPECT_CALL(mio, readRestBuffer).WillOnce(Return("abacabadabacaba"));
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(ms, saveToFile).WillOnce(Return(RequestResult(false, "")));
    SaveToFileState state;
    state.execute(mctx, mf);
}