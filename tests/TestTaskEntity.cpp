//
// Created by denis on 14.07.20.
//

#include <gtest/gtest.h>
#include "api/TaskDTO.h"
#include "api/TaskDTO.cpp"

class TaskEntityTest : public ::testing::Test {

};

TEST_F(TaskEntityTest, noRefrenceCorruption) {
    Task t {"name", Task::Priority::NONE, "lbl", 2020};
    TaskDTO x(1, std::make_shared<Task>(t));
    auto y = x;
    EXPECT_EQ(x.getName(), "name");
    EXPECT_EQ(x.getPriority(), Task::Priority::NONE);
    EXPECT_EQ(x.getLabel(), "lbl");
    EXPECT_EQ(x.getDate(), 2020);
}

TEST_F(TaskEntityTest, correctCopy) {
    Task t {"name", Task::Priority::NONE, "lbl", 2020};
    TaskDTO x(1, std::make_shared<Task>(t));
    auto y = x;
    EXPECT_EQ(y.getId(), 1);
    EXPECT_EQ(y.getName(), "name");
    EXPECT_EQ(y.getPriority(), Task::Priority::NONE);
    EXPECT_EQ(y.getLabel(), "lbl");
    EXPECT_EQ(y.getDate(), 2020);
}
