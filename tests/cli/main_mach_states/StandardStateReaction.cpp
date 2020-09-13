//
// Created by denis on 13.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockKeywordTokenizer.h"
using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;

#define STATE_MUST_SWITCH(SubState, getInstanceMethod, keyword)                 \
    MockStateFactory mf;                                                        \
    EXPECT_CALL(mf, getInstanceMethod).WillOnce(Return(nullptr));               \
    NiceMock<MockContext> mctx;                                                 \
    NiceMock<MockIO> mio;                                                       \
    auto tokenizer = std::make_unique<NiceMock<MockKeywordTokenizer>>();        \
    ON_CALL(*tokenizer, read(Truly([&mio] (ConsoleIOInterface& io) {            \
        return &io == &mio;                                                     \
    }))).WillByDefault(Return(keyword));                                        \
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));                         \
    SubState state(std::move(tokenizer));                                       \
    state.execute(mctx, mf);


#define STATE_MUST_SWITCH_SPEC_KEYWORDS(SubState) \
    std::vector<std::string> must_exit = {        \
            "__exit__",                           \
            "  __exit__  ",                       \
            "d  ds__exit__sad  "                  \
    };                                            \
    std::vector<std::string> must_abort = {       \
        "__abort__",                              \
        "  __abort__  ",                          \
        "d  dd__abort__1  "                       \
    };                                            \
    for (std::string inp : must_exit) {           \
        MockStateFactory mf;                       \
        NiceMock<MockContext> mctx;               \
        NiceMock<MockIO> mio(inp);                \
        ON_CALL(mctx, getIO)                      \
                .WillByDefault(ReturnRef(mio));   \
        ASSERT_EQ(SubState.execute(mctx, mf), nullptr); \
    }                                                   \
    for (std::string inp : must_abort) {           \
        MockStateFactory mf;                       \
        EXPECT_CALL(mf, getInstanceOfParseCommand).WillOnce(Return(nullptr)); \
        NiceMock<MockContext> mctx;               \
        NiceMock<MockIO> mio(inp);                \
        ON_CALL(mctx, getIO)                      \
                .WillByDefault(ReturnRef(mio));   \
        SubState.execute(mctx, mf); \
    }


#define INPUT_STATE_MUST_SWITCH(InputSubState, getInstanceMethod, InputResult)                  \
    auto mit_fsm = std::make_unique<MockInputTaskStateMachine>();                               \
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputResult));                                   \
    ON_CALL(*mit_fsm, extractTask).WillByDefault(Return(                                        \
            TaskDTO::create("", TaskPriority::SECOND, "",                                       \
                            boost::gregorian::day_clock::local_day())                           \
    ));                                                                                         \
    MockStateFactory mf;                                                                        \
    EXPECT_CALL(mf, getInstanceMethod).WillOnce(Return(nullptr));                               \
    NiceMock<MockIO> mio;                                                                       \
    NiceMock<MockContext> mctx;                                                                 \
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));                                         \
    ON_CALL(mctx, fillTaskBuffer).WillByDefault(Return());                                      \
    InputSubState state(std::move(mit_fsm));                                                   \
    state.execute(mctx, mf);

#define INPUT_STATE_MUST_RETURN_NULL(InputSubState, InputResult)                                \
    auto mit_fsm = std::make_unique<MockInputTaskStateMachine>();                               \
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputResult));                                   \
    ON_CALL(*mit_fsm, extractTask).WillByDefault(Return(                                        \
            TaskDTO::create("", TaskPriority::SECOND, "",                                       \
                            boost::gregorian::day_clock::local_day())                           \
    ));                                                                                         \
    MockStateFactory mf;                                                                        \
    NiceMock<MockIO> mio;                                                                       \
    NiceMock<MockContext> mctx;                                                                 \
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));                                         \
    ON_CALL(mctx, fillTaskBuffer).WillByDefault(Return());                                      \
    InputSubState state(std::move(mit_fsm));                                                   \
    ASSERT_EQ(state.execute(mctx, mf), nullptr);