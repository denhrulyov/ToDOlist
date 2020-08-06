//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <api/TaskAPI.h>

using namespace boost::gregorian;

class TaskServiceTest : public ::testing::Test {

public:
    //std::vector<TaskDTO> tasks;
    void SetUp() override {

    }
};

TEST_F(TaskServiceTest, TestAllSubtasksComplete) {
    std::vector<TaskDTO> tasks {
            TaskDTO("t1", Task::Priority::FIRST, "lbl1",
                    day_clock::local_day() + days(2020)),
            TaskDTO("t1", Task::Priority::SECOND, "lbl2",
                    day_clock::local_day() + days(2021)),
            TaskDTO("t3", Task::Priority::FIRST, "lbl3",
                    day_clock::local_day() + days(2024)),
            TaskDTO("t1", Task::Priority::NONE, "lbl1",
                    day_clock::local_day() + days(2020))
    };
    auto root_task = TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                             day_clock::local_day() + days(3000));
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
            TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
            ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id));
}

TEST_F(TaskServiceTest, TestSubTaskAdded) {
    TaskService ts = task_api::createService();
    TaskID id = ts.addTask(
            TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
    ).getCreatedTaskID().value();
    TaskID id2 = ts.addSubTask(
            id,
            TaskDTO("t2", Task::Priority::FIRST, "lbl3",
                    day_clock::local_day() + days(3200))
    ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id2));
}

TEST_F(TaskServiceTest, TestDeleteTask) {
    TaskService ts = task_api::createService();
    TaskID id = ts.addTask(
            TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
    ).getCreatedTaskID().value();
    ts.deleteTask(id);
    EXPECT_FALSE(ts.getTaskByID(id));
}

TEST_F(TaskServiceTest, TestPostponeTask) {
    TaskService ts = task_api::createService();
    TaskDTO task = TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                           day_clock::local_day() + days(3000));
    TaskID id = ts.addTask(task).getCreatedTaskID().value();
    ts.postponeTask(id,
                    day_clock::local_day() + days(4000));
    ASSERT_TRUE(ts.getTaskByID(id).has_value());
    EXPECT_EQ(ts.getTaskByID(id)->getDate(),
              day_clock::local_day() + days(4000));
    EXPECT_EQ(ts.getTaskByID(id)->getLabel(), task.getLabel());
    EXPECT_EQ(ts.getTaskByID(id)->getPriority(), task.getPriority());
    EXPECT_EQ(ts.getTaskByID(id)->getName(), task.getName());
}

TEST_F(TaskServiceTest, TestPostponeSubTask) {
    TaskService ts = task_api::createService();
    TaskDTO task = TaskDTO("t1", Task::Priority::THIRD, "lbl5",
            day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO("t2", Task::Priority::SECOND, "lbls",
                              day_clock::local_day() + days(3200));
    TaskID id = ts.addTask(task).getCreatedTaskID().value();
    TaskID id_subtask = ts.addSubTask(id, subtask).getCreatedTaskID().value();
    ts.postponeTask(id_subtask, day_clock::local_day() + days(4000));
    ASSERT_TRUE(ts.getTaskByID(id_subtask).has_value());
    EXPECT_EQ(ts.getTaskByID(id_subtask)->getDate(),
              day_clock::local_day() + days(4000));
    EXPECT_EQ(ts.getTaskByID(id_subtask)->getLabel(), subtask.getLabel());
    EXPECT_EQ(ts.getTaskByID(id_subtask)->getPriority(), subtask.getPriority());
    EXPECT_EQ(ts.getTaskByID(id_subtask)->getName(), subtask.getName());
}

TEST_F(TaskServiceTest, TestPostponeSUBTaskDoesNotBreaksPARENT) {
    TaskService ts = task_api::createService();
    TaskDTO task = TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                           day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO("t2", Task::Priority::SECOND, "lbls",
                              day_clock::local_day() + days(3200));
    TaskID id = ts.addTask(task).getCreatedTaskID().value();
    TaskID id_subtask = ts.addSubTask(id, subtask).getCreatedTaskID().value();
    ts.postponeTask(id_subtask, day_clock::local_day() + days(4000));
    ASSERT_TRUE(ts.getTaskByID(id).has_value());
    EXPECT_EQ(ts.getTaskByID(id)->getDate(), task.getDate());
    EXPECT_EQ(ts.getTaskByID(id)->getLabel(), task.getLabel());
    EXPECT_EQ(ts.getTaskByID(id)->getPriority(), task.getPriority());
    EXPECT_EQ(ts.getTaskByID(id)->getName(), task.getName());
}

TEST_F(TaskServiceTest, TestPostponeSUBTaskDoesNotBreaksSUBTask) {
    TaskService ts = task_api::createService();
    TaskDTO task = TaskDTO("t1", Task::Priority::THIRD, "lbl5",
                           day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO("t2", Task::Priority::SECOND, "lbls",
                              day_clock::local_day() + days(3200));
    TaskDTO subsubtask = TaskDTO("t3", Task::Priority::FIRST, "lblss",
                                 day_clock::local_day() + days(2800));
    TaskID id = ts.addTask(task).getCreatedTaskID().value();
    TaskID id_subtask = ts.addSubTask(id, subtask).getCreatedTaskID().value();
    TaskID id_subsubtask = ts.addSubTask(id_subtask, subsubtask).getCreatedTaskID().value();
    ts.postponeTask(id_subtask,
                    day_clock::local_day() + days(4000));
    ASSERT_TRUE(ts.getTaskByID(id_subsubtask).has_value());
    EXPECT_EQ(ts.getTaskByID(id_subsubtask)->getDate(), subsubtask.getDate());
    EXPECT_EQ(ts.getTaskByID(id_subsubtask)->getLabel(), subsubtask.getLabel());
    EXPECT_EQ(ts.getTaskByID(id_subsubtask)->getPriority(), subsubtask.getPriority());
    EXPECT_EQ(ts.getTaskByID(id_subsubtask)->getName(), subsubtask.getName());
}

