//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/InputSubTaskState.h"
#include "mocks/MockInputTaskStateMachine.h"
#include "mocks/MockInputTaskContext.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "StandardStateReaction.cpp"

class TestInputSubTaskState : public ::testing::Test {

};


TEST_F(TestInputSubTaskState, writeTaskBufferOnSuccess) {
    auto mit_fsm = std::make_unique<MockInputTaskStateMachine>();
    MockInputTaskContext mictx;
    EXPECT_CALL(mictx, getName).WillRepeatedly(Return("name"));
    EXPECT_CALL(mictx, getPriority).WillRepeatedly(Return(TaskPriority::SECOND));
    EXPECT_CALL(mictx, getLabel).WillRepeatedly(Return("label"));
    EXPECT_CALL(mictx, getDate).WillRepeatedly(Return(BoostDate()));
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputTaskStateMachine::Result::SUCCESS));
    EXPECT_CALL(*mit_fsm, getContext).WillOnce(ReturnRef(mictx));
    NiceMock<MockStateFactory> mf;
    NiceMock<MockIO> mio;
    MockContext mctx;
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(mctx, fillTaskBuffer);
    InputSubTaskState state(std::move(mit_fsm));
    state.execute(mctx, mf);
}

TEST_F(TestInputSubTaskState, returnAddSubTaskStateOnSuccess) {
    INPUT_STATE_MUST_SWITCH(InputSubTaskState, getInstanceOfAddSubTaskState,
                            InputTaskStateMachine::Result::SUCCESS)
}

TEST_F(TestInputSubTaskState, returnParseCommandOnFail) {
    INPUT_STATE_MUST_SWITCH(InputSubTaskState, getInstanceOfParseCommand,
                            InputTaskStateMachine::Result::FAIL)
}

TEST_F(TestInputSubTaskState, returnNullptrOnExit) {
    INPUT_STATE_MUST_RETURN_NULL(InputSubTaskState, InputTaskStateMachine::Result::EXIT_PROGRAM);
}
