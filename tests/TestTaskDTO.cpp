//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include "api/TaskDTO.h"

class TestTaskDTO : public ::testing::Test {

};


TEST_F(TestTaskDTO, correctCopy) {
    Task t = Task::create("name", Task::Priority::NONE, "lbl", 2020);
    TaskDTO x(TaskID(1), t);
    auto y = x;
    EXPECT_EQ(y.getId(), 1);
    EXPECT_EQ(y.getName(), "name");
    EXPECT_EQ(y.getPriority(), Task::Priority::NONE);
    EXPECT_EQ(y.getLabel(), "lbl");
    EXPECT_EQ(y.getDate(), 2020);
}
