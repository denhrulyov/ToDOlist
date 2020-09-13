//
// Created by denis on 13.09.20.
//

#include "cli/state_machines/input_task/InputTaskContext.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/MockIO.h"

class InputTaskContextTest : public ::testing::Test {

};

using ::testing::NiceMock;

TEST_F(InputTaskContextTest, AllFieldAreNulloptWhenJustInit) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    ASSERT_FALSE(ctx.getDate() || ctx.getName() || ctx.getPriority() || ctx.getPriority());
}

TEST_F(InputTaskContextTest, IOisInjectedByConstructor) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    ASSERT_EQ(&ctx.getIO(), &mio);
}


TEST_F(InputTaskContextTest, NameIsFilled) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    std::string name = "name";
    ctx.setName(name);
    ASSERT_TRUE(ctx.getName());
    ASSERT_EQ(ctx.getName(), name);
}

TEST_F(InputTaskContextTest, PriorIsFilled) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    TaskPriority priority = TaskPriority::THIRD;
    ctx.setPriority(priority);
    ASSERT_TRUE(ctx.getPriority());
    ASSERT_EQ(ctx.getPriority(), priority);
}

TEST_F(InputTaskContextTest, LabelIsFilled) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    std::string label = "label";
    ctx.setLabel(label);
    ASSERT_TRUE(ctx.getLabel());
    ASSERT_EQ(ctx.getLabel(), label);
}

TEST_F(InputTaskContextTest, DateIsFilled) {
    NiceMock<MockIO> mio;
    InputTaskContext ctx(mio);
    BoostDate date = boost::gregorian::day_clock::local_day() + boost::gregorian::days(10);
    ctx.setDate(date);
    ASSERT_TRUE(ctx.getDate());
    ASSERT_EQ(ctx.getDate(), date);
}