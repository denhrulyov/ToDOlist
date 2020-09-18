//
// Created by denis on 14.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockIO.h"
#include "mocks/MockInputTaskContext.h"
#include "cli/state_machines/input_task/ParseState.h"

class TestParseState : public ::testing::Test {

};

class FakeParseState : public ParseState {

public:
    void     print(InputTaskContextInterface &) override {};
    MOCK_METHOD(Event, processInput, (InputTaskContextInterface &), (override));
    void     help(InputTaskContextInterface &) override {};
};

using ::testing::ReturnRef;
using ::testing::NiceMock;

TEST(FakeParseState, ReactToSpecKeywords) {
    FakeParseState ps;
    EXPECT_CALL(ps, processInput).Times(0);
    std::vector<std::string> must_exit = {
            "__exit__",
            "  __exit__  ",
            "d  ds__exit__sad  "
    };
    std::vector<std::string> must_abort = {
        "__abort__",
        "  __abort__  ",
        "d  dd__abort__1  "
    };
    for (std::string inp : must_exit) {
        NiceMock<MockInputTaskContext> mctx;
        MockIO io(inp);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.execute(mctx), ParseState::Event::EXIT);
    }
    for (std::string inp : must_abort) {
        NiceMock<MockInputTaskContext> mctx;
        MockIO io(inp);
        ON_CALL(mctx, getIO).WillByDefault(ReturnRef(io));
        ASSERT_EQ(ps.execute(mctx), ParseState::Event::ABORT);
    }
}
