//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include "api/TaskDTO.h"
#include "api/TaskDTO.cpp"
#include "api/UserTaskID.cpp"

class TestTaskDTO : public ::testing::Test {

};


TEST_F(TestTaskDTO, correctCopy) {
    Task t {"name", Task::Priority::NONE, "lbl", 2020};
    TaskDTO x(UserTaskID({1, 2}), t);
    auto y = x;
    EXPECT_EQ(y.getId().getLevelIndices().at(0), 1);
    EXPECT_EQ(y.getId().getLevelIndices().at(1), 2);
    EXPECT_EQ(y.getName(), "name");
    EXPECT_EQ(y.getPriority(), Task::Priority::NONE);
    EXPECT_EQ(y.getLabel(), "lbl");
    EXPECT_EQ(y.getDate(), 2020);
}
