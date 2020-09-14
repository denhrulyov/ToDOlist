//
// Created by denis on 13.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockStateFactory.h"
#include "mocks/MockContext.h"
#include "mocks/MockInputTaskContext.h"
#include "mocks/MockKeywordTokenizer.h"
#include "mocks/MockService.h"
using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::Truly;

#define STATE_MUST_SWITCH(SubState, getInstanceMethod, keyword)                 \
    MockStateFactory mf;                                                        \
    EXPECT_CALL(mf, getInstanceMethod).WillOnce(Return(nullptr));               \
    NiceMock<MockService> ms;                                                    \
    ON_CALL(ms, deleteTask).WillByDefault(Return(TaskModificationResult::success())); \
    ON_CALL(ms, addTask).WillByDefault(Return(TaskCreationResult::success(TaskID(1)))); \
    ON_CALL(ms, addSubTask).WillByDefault(Return(TaskCreationResult::success(TaskID(1)))); \
    NiceMock<MockContext> mctx;                                                 \
    ON_CALL(mctx, getTaskBuffer).WillByDefault(Return(TaskDTO::create(          \
            TaskID(3),                                  \
            "name",                                     \
            TaskPriority::SECOND,                       \
            "label",                                    \
            boost::gregorian::day_clock::local_day(),   \
            true)));                                    \
    ON_CALL(mctx, getBufferedId).WillByDefault(Return(TaskID(1)));              \
    ON_CALL(mctx, getTaskService).WillByDefault(ReturnRef(ms));                 \
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
    NiceMock<MockInputTaskContext> mictx;                                                       \
    ON_CALL(mictx, getName).WillByDefault(Return("name"));                                     \
    ON_CALL(mictx, getPriority).WillByDefault(Return(TaskPriority::SECOND));                   \
    ON_CALL(mictx, getLabel).WillByDefault(Return("label"));                                   \
    ON_CALL(mictx, getDate).WillByDefault(Return(BoostDate()));                                \
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputResult));                                   \
    ON_CALL(*mit_fsm, getContext).WillByDefault(ReturnRef(mictx));                              \
    MockStateFactory mf;                                                                        \
    EXPECT_CALL(mf, getInstanceMethod).WillOnce(Return(nullptr));                               \
    NiceMock<MockIO> mio;                                                                       \
    NiceMock<MockContext> mctx;                                                                 \
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));                                         \
    ON_CALL(mctx, fillTaskBuffer).WillByDefault(Return());                                      \
    InputSubState state(std::move(mit_fsm));                                                   \
    state.execute(mctx, mf);

#define INPUT_STATE_MUST_RETURN_NULL(InputSubState, InputResult)                                \
        auto mit_fsm = std::make_unique<MockInputTaskStateMachine>();                           \
    MockInputTaskContext mictx;                                                                 \
    EXPECT_CALL(mictx, getName).WillRepeatedly(Return("name"));                                 \
    EXPECT_CALL(mictx, getPriority).WillRepeatedly(Return(TaskPriority::SECOND));               \
    EXPECT_CALL(mictx, getLabel).WillRepeatedly(Return("label"));                                \
    EXPECT_CALL(mictx, getDate).WillRepeatedly(Return(BoostDate()));                            \
    EXPECT_CALL(*mit_fsm, run).WillOnce(Return(InputResult));                                   \
    ON_CALL(*mit_fsm, getContext).WillByDefault(ReturnRef(mictx));                              \
    MockStateFactory mf;                                                                        \
    NiceMock<MockIO> mio;                                                                       \
    NiceMock<MockContext> mctx;                                                                 \
    ON_CALL(mctx, getIO).WillByDefault(ReturnRef(mio));                                         \
    ON_CALL(mctx, fillTaskBuffer).WillByDefault(Return());                                      \
    InputSubState state(std::move(mit_fsm));                                                   \
    ASSERT_EQ(state.execute(mctx, mf), nullptr);