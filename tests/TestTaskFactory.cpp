//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include "memory_model/TaskFactory.h"
#include "memory_model/TaskFactory.cpp"


class TestTaskFactory : public ::testing::Test {

};

TEST_F(TestTaskFactory, ptrIsValid) {
    TaskFactory ts;
    auto task = ts.createTask(
            TaskDTO("name", Task::Priority::NONE, "lbl", 2020));
    EXPECT_EQ(task.name, "name");
    EXPECT_EQ(task.priority, Task::Priority::NONE);
    EXPECT_EQ(task.label, "lbl");
    EXPECT_EQ(task.date, 2020);
}