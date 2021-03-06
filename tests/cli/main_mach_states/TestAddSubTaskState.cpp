//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/AddSubTaskState.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StandardStateReaction.cpp"

class TestAddSubTaskState : public ::testing::Test {

};

TEST_F(TestAddSubTaskState, WillReactToYesKeyword) {
    STATE_MUST_SWITCH(AddSubTaskState, getInstanceOfParseCommand, Keyword::YES);
}

TEST_F(TestAddSubTaskState, WillReactToNoKeyword) {
    STATE_MUST_SWITCH(AddSubTaskState, getInstanceOfParseCommand, Keyword::NO);
}