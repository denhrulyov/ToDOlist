//
// Created by denis on 13.09.20.
//

#ifndef TODOLIST_MOCKINPUTTASKSTATEMACHINE_H
#define TODOLIST_MOCKINPUTTASKSTATEMACHINE_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/input_task/InputTaskStateMachine.h"

class MockInputTaskStateMachine : public InputTaskStateMachine {

public:
    MockInputTaskStateMachine() : InputTaskStateMachine(nullptr, nullptr) {}
    MOCK_METHOD(Result, run, (), (override));
    MOCK_METHOD(TaskDTO, extractTask, (), (override));
};

#endif //TODOLIST_MOCKINPUTTASKSTATEMACHINE_H
