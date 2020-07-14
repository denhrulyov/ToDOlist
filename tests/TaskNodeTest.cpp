#include <gtest/gtest.h>
#include "../src/memory_model/TaskNode.h"
#include "../src/memory_model/TaskNode.cpp"

class TaskNodeTest : public ::testing::Test {

};

TEST_F(TaskNodeTest, correctConstruction) {
    TaskNode tst(1, std::move(std::make_unique<Task>(Task {"a", Task::Priority::NONE, "lbl", 2020})));
    ASSERT_EQ(tst.getId(), 1);
    ASSERT_EQ(tst.getTask().name, "a");
    ASSERT_EQ(tst.getTask().priority, Task::Priority::NONE);
    ASSERT_EQ(tst.getTask().label, "lbl");
    ASSERT_EQ(tst.getTask().date, 2020);
}

