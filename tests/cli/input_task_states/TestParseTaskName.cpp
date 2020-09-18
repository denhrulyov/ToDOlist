//
// Created by denis on 14.09.20.
//

#include "cli/state_machines/input_task/ParseTaskName.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockIO.h"
#include "mocks/MockInputTaskContext.h"


class TestParseTaskName : public ::testing::Test {

};

using ::testing::ReturnRef;

TEST_F(TestParseTaskName, WontPassEmptyName) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    MockIO io("");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
    ASSERT_EQ(ps.processInput(mctx), ParseState::Event::INCORRECT);
}

TEST_F(TestParseTaskName, WillPassAnyNonEmptyName) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    MockIO io("ds _d12ds *_dad");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
    ASSERT_EQ(ps.processInput(mctx), ParseState::Event::SUCCESS);
}