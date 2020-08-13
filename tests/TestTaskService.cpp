//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <api/Service.h>
#include "utils/data_transfer/TaskDTOConverter.h"
#include "utils/task_io/ConsoleTaskIO.h"

using ::testing::Return;
using ::testing::NiceMock;

using namespace boost::gregorian;

class TaskServiceTest : public ::testing::Test {

public:
    //std::vector<TaskDTO> tasks;
    void SetUp() override {

    }
};

class MockStorage : public TaskStorageInterface {

public:
  MOCK_METHOD(std::weak_ptr<TaskNode>, getTaskByID, (TaskID), (override));
  MOCK_METHOD(Result, addTask, (const std::shared_ptr<TaskNode>&), (override));
  MOCK_METHOD(Result, eraseTask, (TaskID), (override));
};

template<class T>
class MockView : public PriorityViewInterface<T> {

public:
    MOCK_METHOD(void, addToView, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(std::vector<std::weak_ptr<TaskNode>>, getAllWithConstraint, (const T&), (override));
    MOCK_METHOD(void, removeFromView, (TaskID), (override));
};

class MockLinkManager : public LinkManagerInterface {
public:
    MOCK_METHOD(void, linkSubTask, (const std::weak_ptr<TaskNode>&, const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, setLinks, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, removeLinks, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, moveInboundLinks, (const std::weak_ptr<TaskNode>&, const std::weak_ptr<TaskNode>&), (override));
};



TEST_F(TaskServiceTest, TestAllSubtasksComplete) {
    std::vector ids = {TaskID(0), TaskID(2), TaskID(3), TaskID(4)};
    std::vector<std::shared_ptr<TaskNode>> tasks {
            std::make_shared<TaskNode>(
                    ids[0],
                    Task::create("t1", TaskPriority::FIRST, "lbl1",
                            day_clock::local_day() + days(2020))
                            ),
            std::make_shared<TaskNode>(
                    ids[1],
                    Task::create("t1", TaskPriority::SECOND, "lbl2",
                            day_clock::local_day() + days(2021))
                            ),
            std::make_shared<TaskNode>(
                    ids[2],
                    Task::create("t3", TaskPriority::FIRST, "lbl3",
                            day_clock::local_day() + days(2024))
                            ),
            std::make_shared<TaskNode>(
                    ids[3],
                    Task::create("t1", TaskPriority::NONE, "lbl1",
                            day_clock::local_day() + days(2020))
                            )
    };


    MockStorage* ms = new NiceMock<MockStorage>;
    for (auto node : tasks) {
        ON_CALL(*ms, getTaskByID(node->getId()))
                .WillByDefault(Return(
                        std::weak_ptr(node)
                ));
    }
    MockView<date>* mw = new MockView<date>;
    ON_CALL(*mw, getAllWithConstraint(day_clock::local_day() + years(100)))
            .WillByDefault(Return(
                    std::vector<std::weak_ptr<TaskNode>>
                                {tasks[0],
                                 tasks[1],
                                 tasks[2],
                                 tasks[3]}
            ));
    EXPECT_CALL(*mw, getAllWithConstraint(day_clock::local_day() + years(100)));

    auto root_task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                             day_clock::local_day() + days(3000));
    TaskService ts = TaskService(   std::unique_ptr<MockStorage>(ms),
                                    std::unique_ptr<MockView<boost::gregorian::date>>(mw),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    auto parent = std::shared_ptr<TaskNode>(nullptr);
    for (const auto& task : tasks) {
        if (parent) {
            parent->addSubtask(task);
            task->setParent(parent);
        }
        parent = task;
    }
    ts.complete(tasks[0]->getId());
    for (const auto& dto : ts.getAllTasks()) {
        EXPECT_TRUE(dto.isCompleted());
    }
}

TEST_F(TaskServiceTest, TestTaskAdded) {
    TaskService ts = service::createService();
    TaskID id = ts.addTask(
            TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
            ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id));
}

TEST_F(TaskServiceTest, TestSubTaskAdded) {
    TaskService ts = service::createService();
    TaskID id = ts.addTask(
            TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
    ).getCreatedTaskID().value();
    TaskID id2 = ts.addSubTask(
            id,
            TaskDTO::create("t2", TaskPriority::FIRST, "lbl3",
                    day_clock::local_day() + days(3200))
    ).getCreatedTaskID().value();
    EXPECT_TRUE(ts.getTaskByID(id2));
}

TEST_F(TaskServiceTest, TestDeleteTask) {
    TaskService ts = service::createService();
    TaskID id = ts.addTask(
            TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000))
    ).getCreatedTaskID().value();
    ts.deleteTask(id);
    EXPECT_FALSE(ts.getTaskByID(id));
}

TEST_F(TaskServiceTest, TestPostponeTask) {
    TaskService ts = service::createService();
    TaskDTO task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
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
    TaskService ts = service::createService();
    TaskDTO task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
            day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO::create("t2", TaskPriority::SECOND, "lbls",
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
    TaskService ts = service::createService();
    TaskDTO task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                           day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO::create("t2", TaskPriority::SECOND, "lbls",
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
    TaskService ts = service::createService();
    TaskDTO task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                           day_clock::local_day() + days(3000));
    TaskDTO subtask = TaskDTO::create("t2", TaskPriority::SECOND, "lbls",
                              day_clock::local_day() + days(3200));
    TaskDTO subsubtask = TaskDTO::create("t3", TaskPriority::FIRST, "lblss",
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

