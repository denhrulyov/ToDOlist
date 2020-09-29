//
// Created by denis on 23.09.20.
//

#include "mocks/CoreMocks.h"
#include "core/memory_model/TaskModel.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;
using namespace boost::gregorian;

/***************************************************************************************************/

class TaskModelTest : public ::testing::Test {

};


/***************************************************************************************************/

namespace task_model_test {

    const auto
    pointer_to_same(const std::weak_ptr<TaskNode> &to_cmp) {
        return [&] (const std::weak_ptr<TaskNode> &nd) {
            return nd.lock().get() == to_cmp.lock().get();
        };
    }


    auto sample_nodes(const std::size_t slice = 4) {
        const std::vector<TaskID> ids = {TaskID(1), TaskID(2), TaskID(3), TaskID(4)};
        const std::vector<std::shared_ptr<TaskNode>> tasks{
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
        return std::vector<std::shared_ptr<TaskNode>>(tasks.begin(), tasks.begin() + slice);
    }


    template<class collection>
    std::unique_ptr<MockStorage> create_fixed_mock_storage(const collection &tasks) {
        auto ms = std::make_unique<NiceMock<MockStorage>>();
        for (auto task : tasks) {
            TaskID id = task->getId();
            ON_CALL(*ms, getTaskByID(id))
                    .WillByDefault(Return(task));
        }
        return std::move(ms);
    }

    template<class collection>
    std::pair<
            std::shared_ptr<TaskNode>,
            std::vector<std::shared_ptr<TaskNode>>
    >
    create_sample_structure_1(const collection &tasks) {
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
        return {sample_parent, std::vector<std::shared_ptr<TaskNode>>(tasks.begin() + 1, tasks.end())};
    }
}


TEST_F(TaskModelTest, TestTaskAddedToStorage) {
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

    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    ts.addTask(sample_task);
}

TEST_F(TaskModelTest, TestErrorResultIfNoParentToAddSubtask) {
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

    TaskModel tm =     TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    EXPECT_FALSE(tm.addSubTask(id, sample_task).getSuccessStatus());
}


TEST_F(TaskModelTest, TestErrorResultOfAddSubTaskIfErrorInStorage) {
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
    auto ms = task_model_test::create_fixed_mock_storage(std::vector<std::shared_ptr<TaskNode>> {sample_node});
    ON_CALL(*ms, addTask)
            .WillByDefault(Return(TaskStorageInterface::Result::FAILURE));
    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    //___________
    // Exercise mehod testing
    EXPECT_FALSE(ts.addSubTask(id, sample_task).getSuccessStatus());
}

TEST_F(TaskModelTest, TestTaskLinksSet) {
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
    TaskModel ts = TaskModel(   std::make_unique<MockStorage>(),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    //___________
    // Exercise mehod testing
    ts.addTask(sample_task);
}

TEST_F(TaskModelTest, TestSubTaskLinked) {

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
                        /*parent*/Truly(task_model_test::pointer_to_same(std::weak_ptr(sample_parent))),
                        /*child*/ _
                )).Times(1);
    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.addSubTask(
            parent,
            TaskDTO::create("t2", TaskPriority::FIRST, "lbl3",
                            day_clock::local_day() + days(3200))
    );
}

TEST_F(TaskModelTest, TestDropTaskDeletesItFromStorage) {
    auto tasks = task_model_test::sample_nodes(1);
    TaskID id(tasks[0]->getId());
    auto ms = task_model_test::create_fixed_mock_storage(tasks);
    EXPECT_CALL(*ms, eraseTask(id)).Times(1);
    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    ts.dropTask(id);
}

TEST_F(TaskModelTest, TestDropTaskDeletesAllChildrenFromStorage) {
    auto tasks = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(tasks);
    auto ms = task_model_test::create_fixed_mock_storage(tasks);
    EXPECT_CALL(*ms, eraseTask).Times(AnyNumber());
    for (auto child : children) {
        EXPECT_CALL(*ms, eraseTask(child->getId())).Times(1);
    }
    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    ts.dropTask(parent->getId());
}

TEST_F(TaskModelTest, TestDeleteTaskDeletesItsLinks) {
    auto tasks = task_model_test::sample_nodes(1);
    auto mlm = std::make_unique<MockLinkManager>();
    EXPECT_CALL(*mlm,
                removeLinks).Times(AnyNumber());
    EXPECT_CALL(*mlm,
                removeLinks(
                        Truly(task_model_test::pointer_to_same(std::weak_ptr(tasks[0])))
                )).Times(1);
    TaskModel ts = TaskModel(   std::move(task_model_test::create_fixed_mock_storage(tasks)),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.dropTask(tasks[0]->getId());
}

TEST_F(TaskModelTest, TestDeleteTaskDeletesAllChildrenLinks) {
    auto tasks = task_model_test::sample_nodes(5);
    auto [sample_parent, children] = task_model_test::create_sample_structure_1(tasks);
    auto mlm = std::make_unique<MockLinkManager>();
    EXPECT_CALL(*mlm, removeLinks).Times(AnyNumber());
    for (auto child : children) {
        EXPECT_CALL(
                *mlm,
                removeLinks(
                        Truly(task_model_test::pointer_to_same(child))
                )
        )
                .Times(AnyNumber());
    }
    TaskModel ts = TaskModel(   std::move(task_model_test::create_fixed_mock_storage(tasks)),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::move(mlm));
    ts.dropTask(sample_parent->getId());
}

TEST_F(TaskModelTest, TestDeleteTaskReturnsErrorIfNoSuchTask) {
    auto tasks = task_model_test::sample_nodes(1);
    auto ms = std::make_unique<MockStorage>();
    ON_CALL(*ms, getTaskByID)
            .WillByDefault(Return(std::shared_ptr<TaskNode> {nullptr}));
    TaskModel ts = TaskModel(   std::move(ms),
                                    std::make_unique<MockView<date>>(),
                                    std::make_unique<MockView<std::string>>(),
                                    std::make_unique<MockLinkManager>());
    EXPECT_FALSE(ts.dropTask(tasks[0]->getId()).getSuccessStatus());
}


TEST_F(TaskModelTest, TestSetTaskDataLinkManagerMovesLinks) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    using task_model_test::pointer_to_same;
    auto test_replace = children[0];
    EXPECT_CALL(*mlm, moveInboundLinks(
                                Truly(pointer_to_same(test_replace)), _
                                )
               ).Times(1);
    TaskModel ts = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    ts.setTaskData(test_replace->getId(), TaskDTOConverter::getDTO(parent));
}


TEST_F(TaskModelTest, TestSetTaskDataTaskReplacedInStorage) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<NiceMock<MockLinkManager>>();
    using task_model_test::pointer_to_same;
    auto test_replace = children[0];
    EXPECT_CALL(*ms, eraseTask(test_replace->getId())).Times(1);
    EXPECT_CALL(*ms, addTask).Times(1);
    TaskModel ts = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    ts.setTaskData(test_replace->getId(), TaskDTOConverter::getDTO(parent));
}


TEST_F(TaskModelTest, TestSetTaskDataDoNothingOnNotFound) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(children);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    using task_model_test::pointer_to_same;
    auto test_replace = parent;
    EXPECT_CALL(*ms, eraseTask).Times(0);
    EXPECT_CALL(*ms, addTask).Times(0);
    EXPECT_CALL(*mlm, moveInboundLinks).Times(0);
    TaskModel ts = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    ts.setTaskData(test_replace->getId(), TaskDTOConverter::getDTO(parent));
}

TEST_F(TaskModelTest, TestSetCompletedSetsTaskToCompleted) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(children);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    using task_model_test::pointer_to_same;
    auto test_replace = parent;
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    tm.setCompleted(children[0]->getId());
    ASSERT_TRUE(children[0]->isComplete());
}

TEST_F(TaskModelTest, TestSetCompletedDoesNotTouchSubTasks) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(children);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    using task_model_test::pointer_to_same;
    auto test_replace = parent;
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    tm.setCompleted(children[0]->getId());
    for (int i = 1; i < children.size(); ++i) {
        ASSERT_FALSE(children[i]->isComplete());
    }
}

TEST_F(TaskModelTest, TestSetCompletedDoesNotTouchParent) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(children);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    auto test_replace = parent;
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    tm.setCompleted(children[0]->getId());
    ASSERT_FALSE(parent->isComplete());
}

TEST_F(TaskModelTest, TestSetCompletedReturnsErrorResultOnBadId) {
    auto nodes = task_model_test::sample_nodes(5);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto ms = task_model_test::create_fixed_mock_storage(children);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    auto test_replace = parent;
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    auto mx = std::max_element(nodes.begin(), nodes.end(),
                               [] (auto& t1, auto& t2) {
                                   return t1->getId() < t2->getId();
                               })->get()->getId().getInt();
    ASSERT_FALSE(tm.setCompleted(TaskID(mx + 1)).getSuccessStatus());
}

TEST_F(TaskModelTest, TestGetTaskData) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    ASSERT_TRUE(tm.getTaskData(nodes[0]->getId()));
    TaskDTO got = tm.getTaskData(nodes[0]->getId()).value();
    ASSERT_EQ(nodes[0]->getTask().getName(), got.getName());
    ASSERT_EQ(nodes[0]->getTask().getPriority(), got.getPriority());
    ASSERT_EQ(nodes[0]->getTask().getLabel(), got.getLabel());
    ASSERT_EQ(nodes[0]->getTask().getDate(), got.getDate());
}

TEST_F(TaskModelTest, NulloptIfNoSuchTask) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    auto mx = std::max_element(nodes.begin(), nodes.end(),
                      [] (auto& t1, auto& t2) {
                          return t1->getId() < t2->getId();
                      })->get()->getId().getInt();
    ASSERT_FALSE(tm.getTaskData(TaskID(mx + 1)));
}


TEST_F(TaskModelTest, GetMethodsCallViewsMethods) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    EXPECT_CALL(*mvd, getAllWithConstraint);
    auto mvl = std::make_unique<MockView<std::string>>();
    EXPECT_CALL(*mvl, getAllWithConstraint);
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    tm.getToDate(BoostDate());
    tm.getWithLabel("label");
}

TEST_F(TaskModelTest, TestGetSubtasks) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(   std::move(ms),
                                std::move(mvd),
                                std::move(mvl),
                                std::move(mlm));
    for (auto node : nodes) {
        auto expected = node->getSubNodes();
        auto real = tm.getSubTasks(node->getId());
        std::sort(expected.begin(), expected.end(), [] (auto n1, auto n2) {
            return n1.lock()->getId() < n2.lock()->getId();
        });
        std::sort(real.begin(), real.end(), [] (auto n1, auto n2) {
            return n1.getId() < n2.getId();
        });
        ASSERT_EQ(real.size(), expected.size());
        for (int i = 0; i < real.size(); ++i) {
            ASSERT_EQ(real[i].getId(), expected[i].lock()->getId());
        }
    }
}

TEST_F(TaskModelTest, TestGetSubtasksTaskReturnsEmptyVector) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    ON_CALL(*ms, getTaskByID)
            .WillByDefault(Return(std::shared_ptr<TaskNode> {nullptr}));
    TaskModel ts = TaskModel(   std::move(ms),
                                std::make_unique<MockView<date>>(),
                                std::make_unique<MockView<std::string>>(),
                                std::make_unique<MockLinkManager>());
    auto mx = std::max_element(nodes.begin(), nodes.end(),
                               [] (auto& t1, auto& t2) {
                                   return t1->getId() < t2->getId();
                               })->get()->getId().getInt();
    EXPECT_TRUE(ts.getSubTasks(TaskID(mx + 1)).empty());
}

TEST_F(TaskModelTest, TestGetSubtasksRecurse) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto[parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(std::move(ms),
                             std::move(mvd),
                             std::move(mvl),
                             std::move(mlm));
    std::function<std::vector<std::shared_ptr<TaskNode>>(const std::shared_ptr<TaskNode>&)>
    traverse = [&](const std::shared_ptr<TaskNode>& node) {
        std::vector<std::shared_ptr<TaskNode>> all = {node};
        for (auto to : node->getSubNodes()) {
            auto part = traverse(to.lock());
            all.insert(all.end(), part.begin(), part.end());
        }
        return all;
    };
    for (auto node : nodes) {
        auto expected = traverse(node);
        expected.erase(expected.begin(), expected.begin() + 1);
        auto real = tm.getSubTasksRecursive(node->getId());
        std::sort(expected.begin(), expected.end(), [](auto n1, auto n2) {
            return n1->getId() < n2->getId();
        });
        std::sort(real.begin(), real.end(), [](auto n1, auto n2) {
            return n1.getId() < n2.getId();
        });
        ASSERT_EQ(real.size(), expected.size());
        for (int i = 0; i < real.size(); ++i) {
            ASSERT_EQ(real[i].getId(), expected[i]->getId());
        }
    }
}

TEST_F(TaskModelTest, TestGetSubtasksRecursiveTaskReturnsEmptyVector) {
    auto nodes = task_model_test::sample_nodes(5);
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    auto [parent, children] = task_model_test::create_sample_structure_1(nodes);
    ON_CALL(*ms, getTaskByID)
            .WillByDefault(Return(std::shared_ptr<TaskNode> {nullptr}));
    TaskModel ts = TaskModel(   std::move(ms),
                                std::make_unique<MockView<date>>(),
                                std::make_unique<MockView<std::string>>(),
                                std::make_unique<MockLinkManager>());
    auto mx = std::max_element(nodes.begin(), nodes.end(),
                               [] (auto& t1, auto& t2) {
                                   return t1->getId() < t2->getId();
                               })->get()->getId().getInt();
    EXPECT_TRUE(ts.getSubTasksRecursive(TaskID(mx + 1)).empty());
}

TEST_F(TaskModelTest, TestGetAllTasks) {
    auto nodes = task_model_test::sample_nodes(5);
    std::vector<std::weak_ptr<TaskNode>> weak_nodes(5);
    std::transform(nodes.begin(), nodes.end(), weak_nodes.begin(), [] (const auto& ptr) {return ptr;});
    auto ms = task_model_test::create_fixed_mock_storage(nodes);
    EXPECT_CALL(*ms, getAllTasks).WillOnce(Return(weak_nodes));
    auto[parent, children] = task_model_test::create_sample_structure_1(nodes);
    auto mvd = std::make_unique<MockView<date>>();
    auto mvl = std::make_unique<MockView<std::string>>();
    auto mlm = std::make_unique<MockLinkManager>();
    TaskModel tm = TaskModel(std::move(ms),
                             std::move(mvd),
                             std::move(mvl),
                             std::move(mlm));
    auto expected = nodes;
    auto real = tm.getAllTasks();
    std::sort(expected.begin(), expected.end(), [](auto n1, auto n2) {
    return n1->getId() < n2->getId();
    });
    std::sort(real.begin(), real.end(), [](auto n1, auto n2) {
    return n1.getId() < n2.getId();
    });
    ASSERT_EQ(real.size(), expected.size());
    for (int i = 0; i < real.size(); ++i) {
        ASSERT_EQ(real[i].getId(), expected[i]->getId());
    }
}
