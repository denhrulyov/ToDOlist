//
// Created by denis on 09.09.20.
//

#ifndef TODOLIST_MOCKSERVICE_H
#define TODOLIST_MOCKSERVICE_H

#include "core/api/TaskServiceInterface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockService : public TaskServiceInterface {

public:
    MOCK_METHOD(std::vector<TaskDTO>, getToday, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getThisWeek, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getAllTasks, (), (override));
    MOCK_METHOD(std::optional<TaskDTO>, getTaskByID, (TaskID), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getAllWithLabel, (const std::string&), (override));


public:
    MOCK_METHOD(TaskCreationResult    , addTask, (const TaskDTO&), (override));
    MOCK_METHOD(TaskCreationResult    , addSubTask, (TaskID, const TaskDTO&), (override));
    MOCK_METHOD(TaskModificationResult, deleteTask, (TaskID ), (override));
    MOCK_METHOD(TaskModificationResult, postponeTask, (TaskID, BoostDate), (override));
    MOCK_METHOD(RequestResult         , complete, (TaskID), (override));
};

#endif //TODOLIST_MOCKSERVICE_H
