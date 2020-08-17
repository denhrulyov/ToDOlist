//
// Created by denis on 06.08.20.
//

#include <gtest/gtest.h>
#include "api/TaskModificationResult.h"

class TestTaskModificationResult : public ::testing::Test {

};

TEST_F(TestTaskModificationResult, CorrectConstructor) {
    TaskModificationResult rr(TaskID(1), false, "error");
    ASSERT_FALSE(rr.getSuccessStatus());
    ASSERT_TRUE(rr.getModifiedTaskID().has_value());
    ASSERT_EQ(rr.getModifiedTaskID().value(), TaskID(1));
    ASSERT_EQ("error", rr.getErrorMessage());
}

TEST_F(TestTaskModificationResult, CorrectConstructorNullopt) {
    TaskModificationResult rr(std::nullopt, false, std::nullopt);
    ASSERT_EQ(false, rr.getSuccessStatus());
    ASSERT_FALSE( rr.getErrorMessage().has_value());
    ASSERT_FALSE( rr.getModifiedTaskID().has_value());
}

TEST_F(TestTaskModificationResult, TestResultTypeCorrect) {
    auto rr = TaskModificationResult::success(TaskID(1));
    ASSERT_TRUE(rr.getSuccessStatus());
    ASSERT_FALSE( rr.getErrorMessage().has_value());
    ASSERT_TRUE( rr.getModifiedTaskID().has_value());
    ASSERT_EQ( rr.getModifiedTaskID().value(), TaskID(1));
}

TEST_F(TestTaskModificationResult, TestResultTypeError) {
    auto rr = TaskModificationResult::error("unknown");
    ASSERT_EQ(false, rr.getSuccessStatus());
    ASSERT_TRUE( rr.getErrorMessage().has_value());
    ASSERT_FALSE( rr.getModifiedTaskID().has_value());
    ASSERT_EQ( rr.getErrorMessage().value(), "unknown");
}

