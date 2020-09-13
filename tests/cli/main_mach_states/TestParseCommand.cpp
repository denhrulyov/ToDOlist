//
// Created by denis on 10.09.20.
//

#include "cli/state_machines/main/states/ParseCommand.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"
#include "StandardTokenReaction.cpp"

class TestParseCommand : public ::testing::Test {

};

TEST_F(TestParseCommand, WillReactToAddKeyword) {
    STATE_MUST_SWITCH(ParseCommand, getInstanceOfParseAddType, Keyword::ADD);
}

TEST_F(TestParseCommand, WillReactToShowKeyword) {
    STATE_MUST_SWITCH(ParseCommand, getInstanceOfShowState, Keyword::SHOW);
}

TEST_F(TestParseCommand, WillReactToDeleteKeyword) {
    STATE_MUST_SWITCH(ParseCommand, getInstanceOfDeleteStateParseID, Keyword::DELETE);
}

TEST_F(TestParseCommand, ReactSpecKW) {

    ParseCommand state(std::move(std::make_unique<MockKeywordTokenizer>()));
    STATE_MUST_SWITCH_SPEC_KEYWORDS(state);
}