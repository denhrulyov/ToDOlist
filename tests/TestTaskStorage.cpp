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
    Task::create("t1", Task::Priority::FIRST, "lbl1",
            day_clock::local_day() + days(200)),
    Task::create("t2", Task::Priority::NONE, "lbl2",
            day_clock::local_day() + days(200)),
    Task::create("t3", Task::Priority::SECOND, "lbl3",
                 day_clock::local_day() + days(210))
};

TEST_F(TaskStorageTest, TestTasksSaved) {
    TaskStrorage ts(std::make_unique<TaskIDFactory>());
    for (auto task : sample_tasks) {
        TaskID id = ts.createTask(task)->getId();
        EXPECT_TRUE(ts.getTaskByID(id));
    }
}

TEST_F(TaskStorageTest, TestNodeCorrectCreation) {
    TaskStrorage ts(std::make_unique<TaskIDFactory>());
    std::vector<TaskID> ids;
    for (auto task : sample_tasks) {
        ids.push_back(ts.createTask(task)->getId());
    }
    for (std::size_t i = 0; i < ids.size(); ++i) {
        const auto& sample = sample_tasks[i];
        const auto& in_storage = ts.getTaskByID(ids[i])->getTask();
        EXPECT_EQ(sample.getDate(), in_storage.getDate());
        EXPECT_EQ(sample.getLabel(), in_storage.getLabel());
        EXPECT_EQ(sample.getPriority(), in_storage.getPriority());
        EXPECT_EQ(sample.getName(), in_storage.getName());
    }
}

TEST_F(TaskStorageTest, TestCorrectNodeErased) {
    TaskStrorage ts(std::make_unique<TaskIDFactory>());
    std::vector<TaskID> ids;
    for (auto task : sample_tasks) {
        ids.push_back(ts.createTask(task)->getId());
    }
    TaskID id_erase = ids[1];
    ts.eraseTask(id_erase);
    EXPECT_FALSE(ts.getTaskByID(id_erase));
}

TEST_F(TaskStorageTest, TestTaskWasRecreatedByTheSameID) {
    TaskStrorage ts(std::make_unique<TaskIDFactory>());
    std::vector<TaskID> ids;
    for (auto task : sample_tasks) {
        ids.push_back(ts.createTask(task)->getId());
    }
    TaskID id_recreate = ids[1];
    auto new_task = Task::create("new", Task::Priority::THIRD, "new_label",
                                 day_clock::local_day() + days(1005));
    ts.recreateTask(id_recreate, new_task);
    auto new_node = ts.getTaskByID(id_recreate);
    EXPECT_TRUE(new_node);
}

TEST_F(TaskStorageTest, TestTaskRecreatedCompletely) {
    TaskStrorage ts(std::make_unique<TaskIDFactory>());
    std::vector<TaskID> ids;
    for (auto task : sample_tasks) {
        ids.push_back(ts.createTask(task)->getId());
    }
    TaskID id_recreate = ids[1];
    auto old_node = ts.getTaskByID(id_recreate);
    auto new_task = Task::create("new", Task::Priority::THIRD, "new_label",
                                 day_clock::local_day() + days(1005));
    ts.recreateTask(id_recreate, new_task);
    auto new_node = ts.getTaskByID(id_recreate);
    const Task& in_storage = new_node->getTask();
    EXPECT_EQ(new_task.getDate(), in_storage.getDate());
    EXPECT_EQ(new_task.getLabel(), in_storage.getLabel());
    EXPECT_EQ(new_task.getPriority(), in_storage.getPriority());
    EXPECT_EQ(new_task.getName(), in_storage.getName());
    EXPECT_EQ(new_node->isComplete(), old_node->isComplete());
    EXPECT_EQ(new_node->getParent(), old_node->getParent());
    auto new_subs = new_node->getSubtasks();
    auto old_subs = old_node->getSubtasks();
    ASSERT_EQ(old_subs.size(), new_subs.size());
    for (std::size_t i = 0; i < old_subs.size(); ++i) {
        EXPECT_EQ(old_subs[i], new_subs[i]);
    }
}

