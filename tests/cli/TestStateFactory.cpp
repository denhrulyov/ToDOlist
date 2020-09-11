//
// Created by denis on 10.09.20.
//

#include <gtest/gtest.h>
#include "cli/state_machines/main/state_factory/StateFactory.h"
#include "cli/state_machines/main/state_factory/Of.h"

class StateFactoryTest : public ::testing::Test {
public:
    std::shared_ptr<ConsoleIOInterface> io;
    StateFactory sf = StateFactory(*io);
};

template<class State>
void check(StateFactory& sf) {
    auto ptr = Of<State>().visit(sf);
    ASSERT_EQ(ptr.get(), Of<State>().visit(sf).get());
    ASSERT_EQ(ptr.get(), Of<State>().visit(sf).get());
    ASSERT_EQ(ptr.get(), Of<State>().visit(sf).get());
}

TEST_F(StateFactoryTest, FactoryReturnsSameAddSubTaskState) {
    check<AddSubTaskState>(sf);
}

TEST_F(StateFactoryTest, FactoryReturnsSameAddTaskState) {
    check<AddTaskState>(sf);
}

TEST_F(StateFactoryTest, FactoryReturnsSameDeleteTaskState) {
    check<DeleteTaskState>(sf);
}

TEST_F(StateFactoryTest, FactoryReturnsSameInputState_AddTaskState_ParseCommand_) {
    check<InputState<AddTaskState, ParseCommand>>(sf);
}

TEST_F(StateFactoryTest, FactoryReturnsSameInputState_AddSubTaskState_ParseCommand_) {
    check<InputState<AddSubTaskState, ParseCommand>>(sf);
}

TEST_F(StateFactoryTest, ParseAddType) {
    check<ParseAddType>(sf);
}

TEST_F(StateFactoryTest, ParseCommand) {
    check<ParseCommand>(sf);
}

TEST_F(StateFactoryTest, ParseShowTag) {
    check<ParseShowTag>(sf);
}

TEST_F(StateFactoryTest, ShowState) {
    check<ShowState>(sf);
}

TEST_F(StateFactoryTest, StartState) {
    check<StartState>(sf);
}

TEST_F(StateFactoryTest, DeleteStateParseID) {
    check<DeleteStateParseID>(sf);
}

TEST_F(StateFactoryTest, InputTaskParseID) {
    check<InputTaskParseID>(sf);
}