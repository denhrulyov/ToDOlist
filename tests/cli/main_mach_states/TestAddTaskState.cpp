//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/AddTaskState.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "StandardTokenReaction.cpp"



class TestAddTaskState : public ::testing::Test {

};

TEST_F(TestAddTaskState, WillReactToYesKeyword) {
    STATE_MUST_SWITCH(AddTaskState, getInstanceOfParseCommand, Keyword::YES);
}

TEST_F(TestAddTaskState, WillReactNoYesKeyword) {
    STATE_MUST_SWITCH(AddTaskState, getInstanceOfParseCommand, Keyword::YES);
}
