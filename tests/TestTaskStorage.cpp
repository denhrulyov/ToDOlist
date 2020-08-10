//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include "memory_model/TaskStrorage.h"
#include "memory_model/TaskIDFactory.h"

using namespace boost::gregorian;

class TaskStorageTest : public ::testing::Test {

};

const std::vector<Task> sample_tasks {
    Task::create("t1", TaskPriority::FIRST, "lbl1",
            day_clock::local_day() + days(200)),
    Task::create("t2", TaskPriority::NONE, "lbl2",
            day_clock::local_day() + days(200)),
    Task::create("t3", TaskPriority::SECOND, "lbl3",
                 day_clock::local_day() + days(210))
};

TEST_F(TaskStorageTest, TestTasksSaved) {
    TaskStrorage ts;
    int i = 1;
    for (auto task : sample_tasks) {
        TaskID id(i++);
        ts.addTask(std::make_shared<TaskNode>(id, task));
        EXPECT_TRUE(ts.getTaskByID(id).lock());
    }
}

TEST_F(TaskStorageTest, TestCorrectNodeErased) {
    TaskStrorage ts;
    std::vector<TaskID> ids;
    int i = 0;
    for (auto task : sample_tasks) {
        TaskID id(++i);
        ts.addTask(std::make_shared<TaskNode>(id, task));
        ids.push_back(id);
    }
    TaskID id_erase = ids[1];
    ts.eraseTask(id_erase);
    EXPECT_FALSE(ts.getTaskByID(id_erase).lock());
    EXPECT_TRUE(ts.getTaskByID(ids[0]).lock());
}


