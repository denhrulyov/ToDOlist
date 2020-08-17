//
// Created by denis on 04.08.20.
//

#include <gtest/gtest.h>
#include "core/memory_model/data/TaskID.h"

class TaskIDTest : public ::testing::Test {

};

TEST_F(TaskIDTest, TestIDInvalidInIDByDefault) {
    TaskID default_id;
    EXPECT_FALSE(default_id.vaild());
}

TEST_F(TaskIDTest, TestIDCorrectOrder) {
    TaskID id(0);
    TaskID id0(0);
    TaskID id1(1);
    TaskID id2(2);
    TaskID id30(30);
    TaskID id1000(1000);
    EXPECT_LT(id1, id2);
    EXPECT_GT(id2, id1);
    EXPECT_LT(id0, id1000);
    EXPECT_EQ(id, id0);
    EXPECT_GE(id2, id1);
    EXPECT_LE(id1, id30);
}

TEST_F(TaskIDTest, TestUnstrictOrderEdgeCase) {
    TaskID id(0);
    TaskID id0(0);
    EXPECT_LE(id0, id);
    EXPECT_GE(id0, id);
}

TEST_F(TaskIDTest, TestEQ) {
    TaskID id(0);
    TaskID id0(0);
    EXPECT_EQ(id0, id);
}

TEST_F(TaskIDTest, TestCopy) {
    TaskID id(0);
    TaskID id0 = id;
    EXPECT_EQ(id0, id);
}