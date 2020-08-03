#include <gtest/gtest.h>
#include "memory_model/TaskNode.h"

class TaskNodeTest : public ::testing::Test {

};

TEST_F(TaskNodeTest, correctConstruction) {
    auto task = Task::create("a", Task::Priority::NONE, "lbl", 2020);
    TaskNode tst(TaskID(1), task);
    EXPECT_EQ(tst.getId(), 1);
    EXPECT_EQ(tst.getTask().getName(), "a");
    EXPECT_EQ(tst.getTask().getPriority(), Task::Priority::NONE);
    EXPECT_EQ(tst.getTask().getLabel(), "lbl");
    EXPECT_EQ(tst.getTask().getDate(), 2020);
    EXPECT_EQ(tst.getSubtasks().size(), 0);
}

