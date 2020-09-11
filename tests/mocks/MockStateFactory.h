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
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<AddSubTaskState>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<AddTaskState>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<DeleteTaskState>&) ,(override));
    using Visitor_InputState_AddTaskState_ParseCommand__ = Of<InputState<AddTaskState, ParseCommand>>;
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor_InputState_AddTaskState_ParseCommand__&) ,(override));
    using Visitor_InputState_AddSubTaskState_ParseCommand__ = Of<InputState<AddSubTaskState, ParseCommand>>;
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor_InputState_AddSubTaskState_ParseCommand__&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<ParseAddType>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<ParseCommand>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<ParseShowTag>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<ShowState>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<StartState>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<DeleteStateParseID>&) ,(override));
    MOCK_METHOD(std::shared_ptr<State>, getInstance, (const Visitor<InputTaskParseID>&) ,(override));
};


#endif //TODOLIST_MOCKSTATEFACTORY_H
