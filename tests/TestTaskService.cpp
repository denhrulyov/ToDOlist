//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <api/TaskAPI.h>

class TaskServiceTest : public ::testing::Test {

public:
    //std::vector<TaskDTO> tasks;
    void SetUp() override {

    }
};

TEST_F(TaskServiceTest, TestAllSubtasksComplete) {
    std::vector<TaskDTO> tasks {
            TaskDTO("t1", Task::Priority::FIRST, "lbl1", 2020),
            TaskDTO("t1", Task::Priority::SECOND, "lbl2", 2021),
            TaskDTO("t3", Task::Priority::FIRST, "lbl3", 2024),
            TaskDTO("t1", Task::Priority::NONE, "lbl1", 2020)
    };
    auto root_task = TaskDTO("t1", Task::Priority::THIRD, "lbl5", 3000);
    TaskService ts = task_api::createService();
    TaskID id_root = ts.addTask(root_task).getCreatedTaskID().value();
    TaskID parent =  id_root;
    for (const auto& dto : tasks) {
        parent = ts.addSubTask(parent, dto).getCreatedTaskID().value();
    }
    ts.complete(id_root);
    for (const auto& dto : ts.getAllTasks()) {
        EXPECT_TRUE(dto.isComplete());
    }
}

TEST_F(TaskServiceTest, TestTaskAdded) {
    TaskService ts = task_api::createService();
    TaskID id = ts.addTask(
            TaskDTO("t1", Task::Priority::THIRD, "lbl5", 3000)
            ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id));
}

TEST_F(TaskServiceTest, TestSubTaskAdded) {
    TaskService ts = task_api::createService();
    TaskID id = ts.addTask(
            TaskDTO("t1", Task::Priority::THIRD, "lbl5", 3000)
    ).getCreatedTaskID().value();
    TaskID id2 = ts.addSubTask(
            id,
            TaskDTO("t2", Task::Priority::FIRST, "lbl3", 3200)
    ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id2));
}

TEST_F(TaskServiceTest, TestDeleteTask) {
    TaskService ts = task_api::createService();
    TaskID id = ts.addTask(
            TaskDTO("t1", Task::Priority::THIRD, "lbl5", 3000)
    ).getCreatedTaskID().value();
    ts.deleteTask(id);
    EXPECT_FALSE(ts.getTaskByID(id));
}
