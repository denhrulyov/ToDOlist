//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_MOCKS_H
#define TODOLIST_MOCKS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/memory_model/data/TaskStorage.h"
#include "core/memory_model/structure/LinkManagerInterface.h"
#include "core/memory_model/view/PriorityViewInterface.h"
#include "core/memory_model/api/TaskRepositoryInterface.h"
#include "core/memory_model/RepositoryCreator.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::Action;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Truly;


class MockStorage : public TaskStorageInterface {

public:
    MOCK_METHOD(std::weak_ptr<TaskNode>, getTaskByID, (TaskID), (override));
    MOCK_METHOD(Result, addTask, (const std::shared_ptr<TaskNode>&), (override));
    MOCK_METHOD(Result, eraseTask, (TaskID), (override));
    MOCK_METHOD(std::vector<std::weak_ptr<TaskNode>>, getAllTasks, (), (override));
};

template<class T>
class MockView : public PriorityViewInterface<T> {

public:
    MOCK_METHOD(void, addToView, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(std::vector<std::weak_ptr<TaskNode>>, getAllWithConstraint, (const T&), (const, override));
    MOCK_METHOD(void, removeFromView, (TaskID), (override));
};

class MockLinkManager : public LinkManagerInterface {
public:
    MOCK_METHOD(void, linkSubTask, (const std::weak_ptr<TaskNode>&, const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, setLinks, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, removeLinks, (const std::weak_ptr<TaskNode>&), (override));
    MOCK_METHOD(void, moveInboundLinks, (const std::weak_ptr<TaskNode>&, const std::weak_ptr<TaskNode>&), (override));
};



class MockModel : public TaskRepositoryInterface {

public:
    MOCK_METHOD(std::vector<TaskDTO>,   getToDate, (const BoostDate&), (const, override));
    MOCK_METHOD(std::optional<TaskDTO>, getTaskData, (TaskID), (const, override));
    MOCK_METHOD(TaskModificationResult, setTaskData, (TaskID, const TaskDTO&), (override));
    MOCK_METHOD(std::vector<TaskDTO>,   getWithLabel, (const std::string&), (const, override));

public:
    MOCK_METHOD(TaskCreationResult,     addTask, (const TaskDTO&), (override));
    MOCK_METHOD(TaskCreationResult,     addSubTask, (TaskID, const TaskDTO&), (override));
    MOCK_METHOD(TaskModificationResult, dropTask, (TaskID), (override));
    MOCK_METHOD(TaskModificationResult, setCompleted, (TaskID), (override));
    MOCK_METHOD(std::vector<TaskDTO>,   getSubTasks, (TaskID id), (const, override));
    MOCK_METHOD(std::vector<TaskDTO>,   getSubTasksRecursive, (TaskID id), (const, override));
    MOCK_METHOD(std::vector<TaskDTO>,   getAllTasks, (), (const, override));
    MOCK_METHOD(std::optional<TaskDTO>, getParentTask, (TaskID id), (const, override));

};

class MockModelCreator : public RepositoryCreator {

public:
    MOCK_METHOD(std::unique_ptr<TaskRepositoryInterface>, CreateModel, (), (override));
};

#endif //TODOLIST_MOCKS_H
