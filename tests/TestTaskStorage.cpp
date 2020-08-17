//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include "memory_model/data/TaskStorage.h"
#include "memory_model/data/TaskIDFactory.h"

using namespace boost::gregorian;

class TaskStorageTest : public ::testing::Test {
public:

    TaskStorageTest()
    : sample_tasks {
            Task::create("t1", TaskPriority::FIRST, "lbl1",
                         day_clock::local_day() + days(200)),
            Task::create("t2", TaskPriority::NONE, "lbl2",
                         day_clock::local_day() + days(200)),
            Task::create("t3", TaskPriority::SECOND, "lbl3",
                         day_clock::local_day() + days(210))
    },
    ids {TaskID(1), TaskID(2), TaskID(3)}
    {}
public:
    const std::vector<Task> sample_tasks;
    const std::vector<TaskID> ids;

public:
    TaskStorage createTestStorage() {
        TaskStorage ts;
        int i = 0;
        for (auto task : sample_tasks) {
            ts.addTask(std::make_shared<TaskNode>(ids[i], task));
            ++i;
        }
        return ts;
    }
};



TEST_F(TaskStorageTest, TestTasksSaved) {
    TaskStorage ts;
    int i = 1;
    for (auto task : sample_tasks) {
        TaskID id(i++);
        ts.addTask(std::make_shared<TaskNode>(id, task));
        EXPECT_TRUE(ts.getTaskByID(id).lock());
    }
}

TEST_F(TaskStorageTest, TestCorrectNodeErased) {
    auto ts = createTestStorage();
    TaskID id_erase = ids[1];
    ts.eraseTask(id_erase);
    EXPECT_FALSE(ts.getTaskByID(id_erase).lock());
    EXPECT_TRUE(ts.getTaskByID(ids[0]).lock());
}

TEST_F(TaskStorageTest, TestNullptrIfNoTask) {
    auto ts = createTestStorage();
    TaskID id_not_added(0);
    EXPECT_FALSE(ts.getTaskByID(id_not_added).lock());
}

TEST_F(TaskStorageTest, TestFailureResultIfNoTaskToDelete) {
    auto ts = createTestStorage();
    TaskID id_not_added(0);
    EXPECT_EQ(ts.eraseTask(id_not_added), TaskStorageInterface::Result::FAILURE);
}

TEST_F(TaskStorageTest, TestFailureResultIfTaskIDAlreadyInStorage) {
    auto ts = createTestStorage();
    TaskID id_not_added(0);
    EXPECT_EQ(ts.addTask(std::make_shared<TaskNode>(ids[0], sample_tasks[0])),
            TaskStorageInterface::Result::FAILURE);
}

