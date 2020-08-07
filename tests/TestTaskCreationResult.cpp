//
// Created by denis on 28.07.20.
//

#include <gtest/gtest.h>
#include "api/TaskCreationResult.h"

class TaskCreationResultTest : public ::testing::Test {

};


TEST_F(TaskCreationResultTest, CorrectConstructor) {
    TaskCreationResult rr(TaskID(2), false, "good");
    ASSERT_EQ(TaskID(2), rr.getCreatedTaskID().value());
    ASSERT_EQ(false, rr.getSuccessStatus());
    ASSERT_EQ("good", rr.getErrorMessage().value());
}


TEST_F(TaskCreationResultTest, TestSuccessValue) {
    EXPECT_FALSE(TaskCreationResult::taskNotFound().getSuccessStatus());
    EXPECT_TRUE(TaskCreationResult::success(TaskID(1)).getSuccessStatus());
}

TEST_F(TaskCreationResultTest, AnyCreatedIDonFailure) {
    EXPECT_EQ(TaskCreationResult::taskNotFound().getCreatedTaskID(), std::nullopt);
}

TEST_F(TaskCreationResultTest, AnyErrorMessageOnSuccess) {
    EXPECT_NE(TaskCreationResult::success(TaskID(1)).getCreatedTaskID(), std::nullopt);
}