//
// Created by denis on 13.09.20.
//

#ifndef TODOLIST_MOCKPARSESTATE_H
#define TODOLIST_MOCKPARSESTATE_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/input_task/ParseState.h"

class MockParseState : public ParseState {

public:
    MOCK_METHOD(void, print, (InputTaskContextInterface &), (override));
    MOCK_METHOD(Event, execute, (InputTaskContextInterface &), (override));
    MOCK_METHOD(void, help, (InputTaskContextInterface &), (override));
    MOCK_METHOD(Event, processInput, (InputTaskContextInterface &), (override));
};


#endif //TODOLIST_MOCKPARSESTATE_H
