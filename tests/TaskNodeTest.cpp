#include <gtest/gtest.h>
#include "memory_model/TaskNode.h"
#include "memory_model/TaskNode.cpp"

class TaskNodeTest : public ::testing::Test {

};

TEST_F(TaskNodeTest, correctConstruction) {
    auto task = std::make_shared<Task>(Task {"a", Task::Priority::NONE, "lbl", 2020});
    auto entity = std::make_shared<TaskDTO>(1, task);
    TaskNode tst(entity);
    EXPECT_EQ(tst.getId(), 1);
    EXPECT_EQ(tst.getTask()->getName(), "a");
    EXPECT_EQ(tst.getTask()->getPriority(), Task::Priority::NONE);
    EXPECT_EQ(tst.getTask()->getLabel(), "lbl");
    EXPECT_EQ(tst.getTask()->getDate(), 2020);
    EXPECT_EQ(tst.getSubtasks().size(), 0);
}

