//
// Created by denis on 09.09.20.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockContext.h"
#include "mocks/MockState.h"
#include "cli/state_machines/main/ConsoleStateMachine.h"

class ConsoleStateMachineTest : public ::testing::Test {

};


using ::testing::Return;

TEST_F(ConsoleStateMachineTest, WillBePrinted) {
    auto mctx = std::make_unique<MockContext>();
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, print).WillOnce(Return());
    EXPECT_CALL(*ms, execute).WillOnce(Return(nullptr));
    ConsoleStateMachine(std::move(mctx), nullptr, ms).run();
}

TEST_F(ConsoleStateMachineTest, WillLoopAppropriateTimes) {
    auto mctx = std::make_unique<MockContext>();
    auto ms1 = std::make_shared<MockState>();
    auto ms2 = std::make_shared<MockState>();
    auto ms3 = std::make_shared<MockState>();
    auto ms4 = std::make_shared<MockState>();
    EXPECT_CALL(*ms1, print).WillOnce(Return());
    EXPECT_CALL(*ms1, execute).WillOnce(Return(ms2));
    EXPECT_CALL(*ms2, print).WillOnce(Return());
    EXPECT_CALL(*ms2, execute).WillOnce(Return(ms3));
    EXPECT_CALL(*ms3, print).WillOnce(Return());
    EXPECT_CALL(*ms3, execute).WillOnce(Return(ms4));
    EXPECT_CALL(*ms4, print).WillOnce(Return());
    EXPECT_CALL(*ms4, execute).WillOnce(Return(nullptr));
    ConsoleStateMachine(std::move(mctx), nullptr, ms1).run();
}
