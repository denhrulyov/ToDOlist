//
// Created by denis on 13.09.20.
//


#include "cli/state_machines/main/states/DeleteTaskState.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "StandardStateReaction.cpp"


class TestDeleteTaskState : public ::testing::Test {

};

TEST_F(TestDeleteTaskState, WillReactToYesKeyword) {
    STATE_MUST_SWITCH(DeleteTaskState, getInstanceOfParseCommand, Keyword::YES);
}

TEST_F(TestDeleteTaskState, WillReactToNoKeyword) {
    STATE_MUST_SWITCH(DeleteTaskState, getInstanceOfParseCommand, Keyword::NO);
}
