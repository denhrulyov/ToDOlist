//
// Created by denis on 10.09.20.
//

#ifndef TODOLIST_MOCKSTATEFACTORY_H
#define TODOLIST_MOCKSTATEFACTORY_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/main/state_factory/StateFactoryInterface.h"
#include "cli/state_machines/main/state_factory/Of.h"

class MockStateFactory : public StateFactoryInterface {

public:
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfAddSubTaskState, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfAddTaskState, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfDeleteTaskState, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfSubTaskInputChain, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfTaskInputChain, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseAddType, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseCommand, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfParseShowTag, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfShowState, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfStartState, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfDeleteStateParseID, () ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstanceOfInputTaskParseID, () ,(override));
};


#endif //TODOLIST_MOCKSTATEFACTORY_H
