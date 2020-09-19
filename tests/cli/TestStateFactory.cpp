//
// Created by denis on 10.09.20.
//

#include <gtest/gtest.h>
#include "mocks/MockContext.h"
#include "cli/state_machines/main/state_factory/StateFactory.h"


using ::testing::NiceMock;
using ::testing::ReturnRef;

class StateFactoryTest : public ::testing::Test {
public:
    MockContext context;
    NiceMock<MockIO> io;
    StateFactory sf = StateFactory(context);

public:
    StateFactoryTest() {
        ON_CALL(context, getIO).WillByDefault(ReturnRef(io));
    }
};


TEST_F(StateFactoryTest, FactoryReturnsSameAddSubTaskState) {
    auto ptr = sf.getInstanceOfAddTaskState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
}

TEST_F(StateFactoryTest, FactoryReturnsSameAddTaskState) {
    auto ptr = sf.getInstanceOfAddSubTaskState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddSubTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddSubTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddSubTaskState().get());
}

TEST_F(StateFactoryTest, FactoryReturnsSameDeleteTaskState) {
    auto ptr = sf.getInstanceOfDeleteTaskState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteTaskState().get());
}

TEST_F(StateFactoryTest, FactoryReturnsSameTaskInputChain) {
    auto ptr = sf.getInstanceOfTaskInputChain();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfTaskInputChain().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfTaskInputChain().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfTaskInputChain().get());
}

TEST_F(StateFactoryTest, FactoryReturnsSameSubTaskInputChain) {
    auto ptr = sf.getInstanceOfSubTaskInputChain();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfSubTaskInputChain().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfSubTaskInputChain().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfSubTaskInputChain().get());
}

TEST_F(StateFactoryTest, ParseAddType) {
    auto ptr = sf.getInstanceOfAddTaskState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
}

TEST_F(StateFactoryTest, ParseCommand) {
    auto ptr = sf.getInstanceOfParseCommand();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfParseCommand().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfParseCommand().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfParseCommand().get());
}

TEST_F(StateFactoryTest, ParseShowTag) {
    auto ptr = sf.getInstanceOfAddTaskState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfAddTaskState().get());
}

TEST_F(StateFactoryTest, ShowState) {
    auto ptr = sf.getInstanceOfShowState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfShowState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfShowState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfShowState().get());
}

TEST_F(StateFactoryTest, StartState) {
    auto ptr = sf.getInstanceOfStartState();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfStartState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfStartState().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfStartState().get());
}

TEST_F(StateFactoryTest, DeleteStateParseID) {
    auto ptr = sf.getInstanceOfDeleteStateParseID();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteStateParseID().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteStateParseID().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfDeleteStateParseID().get());
}

TEST_F(StateFactoryTest, InputTaskParseID) {
    auto ptr = sf.getInstanceOfInputTaskParseID();
    ASSERT_EQ(ptr.get(), sf.getInstanceOfInputTaskParseID().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfInputTaskParseID().get());
    ASSERT_EQ(ptr.get(), sf.getInstanceOfInputTaskParseID().get());
}