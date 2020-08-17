//
// Created by denis on 03.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <api/Service.h>
#include "utils/data_transfer/TaskDTOConverter.h"
#include "utils/task_io/ConsoleTaskIO.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;

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

/***********************************************************************************/
// Utility

const auto pointer_to_same(const std::weak_ptr<TaskNode>& to_cmp) {
    return [&] (const std::weak_ptr<TaskNode>& nd) {
        return nd.lock().get() == to_cmp.lock().get();
    };
}

auto sample_nodes(const std::size_t slice = 4) {
    const std::vector ids = {TaskID(1), TaskID(2), TaskID(3), TaskID(4)};
    const std::vector<std::shared_ptr<TaskNode>> tasks {
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
            ),
            std::make_shared<TaskNode>(
                ids[4],
                Task::create("t99", TaskPriority::SECOND, "lbl2",
                day_clock::local_day() + days(1999))
            )
    };
    return std::vector(tasks.begin(), tasks.begin() + slice);
}

template<class collection>
auto create_fixed_mock_storage(const collection& tasks) {
    auto ms = std::make_unique<NiceMock<MockStorage>>();
    for (auto task : tasks) {
        TaskID id = task->getId();
        ON_CALL(*ms, getTaskByID(id))
                .WillByDefault(Return(task));
    }
    return std::move(ms);
}

template <class collection>
std::pair<
        std::shared_ptr<TaskNode>,
        std::vector<std::shared_ptr<TaskNode>>
        >
create_sample_structure_1 (const collection& tasks) {
    auto sample_parent = tasks[0];
    for (std::size_t i = 1; i < tasks.size() - (tasks.size() > 2); ++i) {
        tasks[i]->setParent(sample_parent);
        sample_parent->addSubtask(tasks[i]);
    }
    if (tasks.size() > 2) {
        (*(tasks.end() - 2))->addSubtask(tasks.back());
        tasks.back()->setParent(*(tasks.end() - 2));
    }
    TaskID parent(sample_parent->getId());
    return {sample_parent, std::vector(tasks.begin() + 1, tasks.end())};
}


/*************************************************************************************/
// Tests

TEST_F(TaskServiceTest, TestAllSubtasksComplete) {
    auto tasks = sample_nodes();
    // Mocks
    auto ms = std::make_unique<NiceMock<MockStorage>>();
    for (auto node : tasks) {
        ON_CALL(*ms, getTaskByID(node->getId()))
                .WillByDefault(Return(
                        std::weak_ptr(node)
                ));
    }
    auto mw = std::make_unique<MockView<date>>();
    ON_CALL(*mw, getAllWithConstraint(day_clock::local_day() + years(100)))
            .WillByDefault(Return(
                    std::vector<std::weak_ptr<TaskNode>>
                                {tasks[0],
                                 tasks[1],
                                 tasks[2],
                                 tasks[3]}
            ));
    // ___________
    // Mock Expectations
    EXPECT_CALL(*mw, getAllWithConstraint(day_clock::local_day() + years(100)));
    //____________
    // Build structure
    auto root_task = TaskDTO::create("t1", TaskPriority::THIRD, "lbl5",
                             day_clock::local_day() + days(3000));
    TaskService ts = TaskService(   std::move(ms),
                                    std::move(mw),
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
    //___________
    // Exercise mehod testing
    ts.complete(tasks[0]->getId());
    //___________
    // Check result
    for (const auto& dto : ts.getAllTasks()) {
        EXPECT_TRUE(dto.isCompleted());
    }
}

TEST_F(TaskServiceTest, TestTaskAddedToStorage) {
    // Sample data
    TaskID id(0);
    auto sample_task = TaskDTO::create("t1", TaskPriority::FIRST, "lbl1",
                                    day_clock::local_day() + days(2020));
    auto sample_node = std::make_shared<TaskNode>(
            id,
            TaskDTOConverter::getTask(sample_task)
    );
    // ___________
    // Mocks
    auto ms = std::make_unique<MockStorage>();
    EXPECT_CALL(*ms, addTask).Times(1);

    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    ts.addTask(sample_task);
}

TEST_F(TaskServiceTest, TestErrorResultIfNoParentToAddSubtask) {
    // Sample data
    TaskID id(0);
    auto sample_task = TaskDTO::create("t1", TaskPriority::FIRST, "lbl1",
                                       day_clock::local_day() + days(2020));
    auto sample_node = std::make_shared<TaskNode>(
            id,
            TaskDTOConverter::getTask(sample_task)
    );
    // ___________
    // Mocks
    auto ms = std::make_unique<MockStorage>();
    ON_CALL(*ms, getTaskByID)
            .WillByDefault(Return(std::shared_ptr<TaskNode>{nullptr}));

    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    EXPECT_FALSE(ts.addSubTask(id, sample_task).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestErrorResultOfAddSubTaskIfErrorInStorage) {
    // Sample data
    TaskID id(0);
    auto sample_task = TaskDTO::create("t1", TaskPriority::FIRST, "lbl1",
                                       day_clock::local_day() + days(2020));
    auto sample_node = std::make_shared<TaskNode>(
            id,
            TaskDTOConverter::getTask(sample_task)
    );
    // ___________
    // Mocks
    auto ms = create_fixed_mock_storage(std::vector {sample_node});
    ON_CALL(*ms, addTask)
            .WillByDefault(Return(TaskStorageInterface::Result::FAILURE));
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    EXPECT_FALSE(ts.addSubTask(id, sample_task).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestTaskLinksSet) {
    // Sample data
    TaskID id(0);
    auto sample_task = TaskDTO::create("t1", TaskPriority::FIRST, "lbl1",
                                       day_clock::local_day() + days(2020));
    auto sample_node = std::make_shared<TaskNode>(
            id,
            TaskDTOConverter::getTask(sample_task)
    );
    // ___________
    // Mocks
    auto mlm = std::make_unique<MockLinkManager>();
    EXPECT_CALL(*mlm, setLinks).Times(1);
    TaskService ts = TaskService(   std::make_unique<MockStorage>(),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    //___________
    // Exercise mehod testing
    ts.addTask(sample_task);
}

TEST_F(TaskServiceTest, TestSubTaskLinked) {

    TaskID parent(1);
    auto sample_parent = std::make_shared<TaskNode>(
            parent,
            Task::create("t1", TaskPriority::THIRD, "lbl5",
                    day_clock::local_day() + days(3000)));
    auto ms = std::make_unique<NiceMock<MockStorage>>();
    ON_CALL(*ms, getTaskByID(parent))
            .WillByDefault(Return(sample_parent));
    ON_CALL(*ms, addTask)
            .WillByDefault(Return(
                    TaskStorageInterface::Result::SUCCESS)
                    );
    auto mlm = std::make_unique<NiceMock<MockLinkManager>>();
    EXPECT_CALL(*mlm,
            linkSubTask(
                    /*parent*/Truly(pointer_to_same(std::weak_ptr(sample_parent))),
                    /*child*/ _
                    )).Times(1);
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.addSubTask(
            parent,
            TaskDTO::create("t2", TaskPriority::FIRST, "lbl3",
                    day_clock::local_day() + days(3200))
    );
}

TEST_F(TaskServiceTest, TestDeleteTaskDeletesItFromStorage) {
    auto tasks = sample_nodes(1);
    TaskID id(tasks[0]->getId());
    auto ms = create_fixed_mock_storage(tasks);
    EXPECT_CALL(*ms, eraseTask(id)).Times(1);
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    ts.deleteTask(id);
}

TEST_F(TaskServiceTest, TestDeleteTaskDeletesAllChildrenFromStorage) {
    auto tasks = sample_nodes(5);
    auto [parent, children] = create_sample_structure_1(tasks);
    auto ms = create_fixed_mock_storage(tasks);
    EXPECT_CALL(*ms, eraseTask).Times(AnyNumber());
    for (auto child : children) {
        EXPECT_CALL(*ms, eraseTask(child->getId())).Times(1);
    }
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    ts.deleteTask(parent->getId());
}

TEST_F(TaskServiceTest, TestDeleteTaskDeletesItsLinks) {
    auto tasks = sample_nodes(1);
    auto mlm = std::make_unique<MockLinkManager>();
    EXPECT_CALL(*mlm,
                removeLinks).Times(AnyNumber());
    EXPECT_CALL(*mlm,
            removeLinks(
                    Truly(pointer_to_same(std::weak_ptr(tasks[0])))
                    )).Times(1);
    TaskService ts = TaskService(   std::move(create_fixed_mock_storage(tasks)),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.deleteTask(tasks[0]->getId());
}

TEST_F(TaskServiceTest, TestDeleteTaskDeletesAllChildrenLinks) {
    auto tasks = sample_nodes(5);
    auto [sample_parent, children] = create_sample_structure_1(tasks);
    auto mlm = std::make_unique<MockLinkManager>();
    EXPECT_CALL(*mlm, removeLinks).Times(AnyNumber());
    for (auto child : children) {
        EXPECT_CALL(
                *mlm,
                removeLinks(
                        Truly(pointer_to_same(child))
                        )
                    )
                    .Times(AnyNumber());
    }
    TaskService ts = TaskService(   std::move(create_fixed_mock_storage(tasks)),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.deleteTask(sample_parent->getId());
}

TEST_F(TaskServiceTest, TestDeleteTaskReturnsErrorIfNoSuchTask) {
    auto tasks = sample_nodes(1);
    auto ms = std::make_unique<MockStorage>();
    ON_CALL(*ms, getTaskByID)
        .WillByDefault(Return(std::shared_ptr<TaskNode> {nullptr}));
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    EXPECT_FALSE(ts.deleteTask(tasks[0]->getId()).getSuccessStatus());
}

TEST_F(TaskServiceTest, TestPostponeTaskReturnsErrorIfNoSuchTask) {
    auto tasks = sample_nodes(1);
    auto ms = std::make_unique<MockStorage>();
    ON_CALL(*ms, getTaskByID)
            .WillByDefault(Return(std::shared_ptr<TaskNode> {nullptr}));
    TaskService ts = TaskService(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    EXPECT_FALSE(
            ts.postponeTask(tasks[0]->getId(),
                    tasks[0]->getTask().getDate() + boost::gregorian::days(1))
                        .getSuccessStatus()
                    );
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

