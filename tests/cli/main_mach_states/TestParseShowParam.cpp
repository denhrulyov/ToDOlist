//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/main/states/ParseAddType.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"
#include "StandardTokenReaction.cpp"

class TestParseShowParam : public ::testing::Test {

};

TEST_F(TestParseShowParam, WillReactToTodayKeyword) {
    STATE_MUST_SWITCH(ParseAddType, getInstanceOfTaskInputChain, Keyword::TODAY);
}

TEST_F(TestParseShowParam, WillReactToShowKeyword) {
    STATE_MUST_SWITCH(ParseAddType, getInstanceOfInputTaskParseID, Keyword::SUBTASK);
}
