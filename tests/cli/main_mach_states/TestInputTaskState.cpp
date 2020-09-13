//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/InputTaskState.h"
#include "mocks/MockInputTaskStateMachine.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "StandardStateReaction.cpp"

using ::testing::Return;
using ::testing::NiceMock;
using ::testing::ReturnRef;

class TestInputTaskState : public ::testing::Test {

};

TEST_F(TestInputTaskState, writeTaskBufferOnSuccess) {
    auto mit_fsm = std::make_unique<MockInputTaskStateMachine>();
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputTaskStateMachine::Result::SUCCESS));
    ON_CALL(*mit_fsm, extractTask).WillByDefault(Return(
            TaskDTO::create("", TaskPriority::SECOND, "",                                       \
                            boost::gregorian::day_clock::local_day())
    ));
    NiceMock<MockStateFactory> mf;
    NiceMock<MockIO> mio;
    MockContext mctx;
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));
    EXPECT_CALL(mctx, fillTaskBuffer);
    InputTaskState state(std::move(mit_fsm));
    state.execute(mctx, mf);
}

TEST_F(TestInputTaskState, returnAddTaskStateOnSuccess) {
    INPUT_STATE_MUST_SWITCH(InputTaskState, getInstanceOfAddTaskState,
                            InputTaskStateMachine::Result::SUCCESS)
}

TEST_F(TestInputTaskState, returnParseCommandOnFail) {
    INPUT_STATE_MUST_SWITCH(InputTaskState, getInstanceOfParseCommand,
                            InputTaskStateMachine::Result::FAIL)
}

TEST_F(TestInputTaskState, returnNullptrOnExit) {
    INPUT_STATE_MUST_RETURN_NULL(InputTaskState, InputTaskStateMachine::Result::EXIT_PROGRAM);
}