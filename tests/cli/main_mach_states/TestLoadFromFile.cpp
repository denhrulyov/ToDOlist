//
// Created by denis on 05.10.20.
//

#include "cli/state_machines/main/states/LoadFromFileState.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockService.h"

using ::testing::ReturnRef;

class LoadFromFileTest : public ::testing::Test {

};

TEST_F(LoadFromFileTest, TestSwitchParseCommand) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    testing::NiceMock<MockContext> mctx;
    MockService ms;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getTaskService).WillOnce(ReturnRef(ms));
    testing::NiceMock<MockIO> mio;
    EXPECT_CALL(mio, readRestBuffer).WillOnce(Return("abacabadabacaba"));
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(ms, loadFromFile).WillOnce(Return(RequestResult::success()));
    LoadFromFileState state;
    state.execute(mctx, mf);
}

TEST_F(LoadFromFileTest, TestSwitchParseCommandOnBad) {
    MockStateFactory mf;
    EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr));
    testing::NiceMock<MockContext> mctx;
    MockService ms;
    std::map<TaskNumber, TaskID> matching;
    EXPECT_CALL(mctx, getTaskService).WillOnce(ReturnRef(ms));
    testing::NiceMock<MockIO> mio;
    EXPECT_CALL(mio, readRestBuffer).WillOnce(Return("abacabadabacaba"));
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(ms, loadFromFile).WillOnce(Return(RequestResult(false, "")));
    LoadFromFileState state;
    state.execute(mctx, mf);
}