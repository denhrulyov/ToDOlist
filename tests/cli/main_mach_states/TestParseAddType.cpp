//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/ParseAddType.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"
#include "StandardStateReaction.cpp"

class TestParseAddType : public ::testing::Test {

};

TEST_F(TestParseAddType, WillReactToTaskKeyword) {
    STATE_MUST_SWITCH(ParseAddType, getInstanceOfTaskInputChain, Keyword::TASK);
}

TEST_F(TestParseAddType, WillReactToShowKeyword) {
    STATE_MUST_SWITCH(ParseAddType, getInstanceOfInputTaskParseID, Keyword::SUBTASK);
}

