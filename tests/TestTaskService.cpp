//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <api/TaskAPI.h>

class TaskNodeTest : public ::testing::Test {

public:
    //std::vector<TaskDTO> tasks;
    void SetUp() override {

    }
};

TEST_F(TaskNodeTest, TestAllSubtasksComplete) {
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
