//
// Created by denis on 10.09.20.
//

#ifndef TODOLIST_MOCKSTATEFACTORY_H
#define TODOLIST_MOCKSTATEFACTORY_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/main/state_factory/StateFactoryInterface.h"

class MockStateFactory : public StateFactoryInterface {

public:
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfAddSubTaskState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfAddTaskState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfCompleteState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfDeleteTaskState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfSubTaskInputChain, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfTaskInputChain, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfLoadFromFileState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseAddType, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseCommand, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParsePostponeDate, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseShowTag, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfPostponeState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfShowState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfStartState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfShowSubTasksState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfDeleteStateParseID, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfInputTaskParseID, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseCompleteID, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParsePostponeID, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfSaveToFileState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfShowSubTasksParseID, (), (override));
};


#endif //TODOLIST_MOCKSTATEFACTORY_H
