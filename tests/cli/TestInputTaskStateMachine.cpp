//
// Created by denis on 14.09.20.
//

#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockIO.h"
#include "mocks/MockInputTaskContext.h"
#include "mocks/MockParseState.h"
#include "mocks/MockParseStateFactory.h"

class TestInputTaskStateMachine : public ::testing::Test {

};

using ::testing::NiceMock;
using ::testing::ReturnRef;

TEST_F(TestInputTaskStateMachine, TestReturnFailResultOnAbortEvent) {
    auto mf = std::make_unique<MockParseStateFactory>();
    auto mctx = std::make_unique<MockInputTaskContext>();
    auto mio = NiceMock<MockIO>();
    ON_CALL(*mctx, getIO).WillByDefault(ReturnRef(mio));
    auto mps = std::make_shared<MockParseState>();
    EXPECT_CALL(*mps, execute).WillOnce(Return(ParseState::Event::ABORT));
    EXPECT_CALL(*mf, getFirstState).WillOnce(Return(mps));
    ASSERT_EQ(InputTaskStateMachine::Result::FAIL,
            InputTaskStateMachine(std::move(mf), std::move(mctx)).run());
}

TEST_F(TestInputTaskStateMachine, TestReturnExiProgramResultOnExitEvent) {
    auto mf = std::make_unique<MockParseStateFactory>();
    auto mctx = std::make_unique<MockInputTaskContext>();
    auto mio = NiceMock<MockIO>();
    ON_CALL(*mctx, getIO).WillByDefault(ReturnRef(mio));
    auto mps = std::make_shared<MockParseState>();
    EXPECT_CALL(*mps, execute).WillOnce(Return(ParseState::Event::EXIT));
    EXPECT_CALL(*mf, getFirstState).WillOnce(Return(mps));
    ASSERT_EQ(InputTaskStateMachine::Result::EXIT_PROGRAM,
              InputTaskStateMachine(std::move(mf), std::move(mctx)).run());
}

TEST_F(TestInputTaskStateMachine, TestWillLoopWhileIncorrect) {
    auto mf = std::make_unique<MockParseStateFactory>();
    auto mctx = std::make_unique<MockInputTaskContext>();
    auto mio = NiceMock<MockIO>();
    ON_CALL(*mctx, getIO).WillByDefault(ReturnRef(mio));
    auto mps = std::make_shared<NiceMock<MockParseState>>();
    EXPECT_CALL(*mps, execute)
        .WillOnce(Return(ParseState::Event::INCORRECT))
        .WillOnce(Return(ParseState::Event::SUCCESS));
    EXPECT_CALL(*mf, getFirstState)
        .WillOnce(Return(mps));
    EXPECT_CALL(*mf, getNextState)
        .WillOnce(Return(nullptr));
    InputTaskStateMachine(std::move(mf), std::move(mctx)).run();
}