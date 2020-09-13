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



