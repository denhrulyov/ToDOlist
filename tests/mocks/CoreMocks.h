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


#endif //TODOLIST_MOCKS_H
