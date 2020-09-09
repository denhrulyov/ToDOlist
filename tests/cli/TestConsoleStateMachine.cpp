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


TEST_F(ConsoleStateMachineTest, WillBePrinted) {
    auto mio = std::make_unique<MockIO>();
    MockState st;
    //ConsoleStateMachine(nullptr, std::move(mio), );
}