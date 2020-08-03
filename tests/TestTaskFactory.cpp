//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include "memory_model/TaskFactory.h"


class TestTaskFactory : public ::testing::Test {

};

TEST_F(TestTaskFactory, ptrIsValid) {
    TaskFactory ts;
    auto task = ts.createTask(
            TaskDTO("name", Task::Priority::NONE, "lbl", 2020));
    EXPECT_EQ(task.getName(), "name");
    EXPECT_EQ(task.getPriority(), Task::Priority::NONE);
    EXPECT_EQ(task.getLabel(), "lbl");
    EXPECT_EQ(task.getDate(), 2020);
}