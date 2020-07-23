#include <gtest/gtest.h>
#include "memory_model/TaskNode.h"
#include "memory_model/TaskNode.cpp"

class TaskNodeTest : public ::testing::Test {

};

TEST_F(TaskNodeTest, correctConstruction) {
    auto task = Task {"a", Task::Priority::NONE, "lbl", 2020};
    TaskNode tst(TaskID(1), task);
    EXPECT_EQ(tst.getId(), 1);
    EXPECT_EQ(tst.getTask().name, "a");
    EXPECT_EQ(tst.getTask().priority, Task::Priority::NONE);
    EXPECT_EQ(tst.getTask().label, "lbl");
    EXPECT_EQ(tst.getTask().date, 2020);
    EXPECT_EQ(tst.getSubtasks().size(), 0);
}

