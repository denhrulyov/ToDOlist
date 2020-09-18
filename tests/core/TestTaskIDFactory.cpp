//
// Created by denis on 04.08.20.
//

#include <gtest/gtest.h>
#include "core/memory_model/data/TaskIDFactory.h"

class TaskIDTest : public ::testing::Test {

};

TEST_F(TaskIDTest, TestDifferentIDsGenerated) {
    TaskIDFactory id_generator;
    std::vector<TaskID> was;
    for (std::size_t i = 0; i < 10; ++i) {
        TaskID generated_id = id_generator.generateID();
        for (TaskID prev_id : was) {
            ASSERT_FALSE(prev_id == generated_id);
        }
        was.push_back(generated_id);
    }
}
