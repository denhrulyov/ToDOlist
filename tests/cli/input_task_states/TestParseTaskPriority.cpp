//
// Created by denis on 14.09.20.
//

#include "cli/state_machines/input_task/ParseTaskName.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockIO.h"
#include "mocks/MockInputTaskContext.h"


class TestParseTaskPriority : public ::testing::Test {

};

using ::testing::ReturnRef;

TEST_F(TestParseTaskPriority, WontPassEmptyString) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    MockIO io("");
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
    ASSERT_EQ(ps.processInput(mctx), ParseState::Event::INCORRECT);
}

TEST_F(TestParseTaskPriority, WillPassFIRST) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    std::vector<std::string> must_pass {"1", "  1", "first","first  ", "  first "};
    for (std::string input : must_pass) {
        MockIO io(input);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.processInput(mctx), ParseState::Event::SUCCESS);
    }
}

TEST_F(TestParseTaskPriority, WillPassSECOND) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    std::vector<std::string> must_pass {"2", "  2", "second","second  ", "  second "};
    for (std::string input : must_pass) {
        MockIO io(input);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.processInput(mctx), ParseState::Event::SUCCESS);
    }
}

TEST_F(TestParseTaskPriority, WillPassTHIRD) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    std::vector<std::string> must_pass {"3", "  3", "third","third  ", "  third "};
    for (std::string input : must_pass) {
        MockIO io(input);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.processInput(mctx), ParseState::Event::SUCCESS);
    }
}

TEST_F(TestParseTaskPriority, WillPassNONE) {
    ParseTaskName ps;
    MockInputTaskContext mctx;
    std::vector<std::string> must_pass {"0", "  0", "none","none  ", "  none "};
    for (std::string input : must_pass) {
        MockIO io(input);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.processInput(mctx), ParseState::Event::SUCCESS);
    }
}

