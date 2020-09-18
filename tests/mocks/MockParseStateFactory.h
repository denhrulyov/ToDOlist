//
// Created by denis on 14.09.20.
//

#ifndef TODOLIST_MOCKPARSESTATEFACTORY_H
#define TODOLIST_MOCKPARSESTATEFACTORY_H

#include "cli/state_machines/input_task/ParseStateFactoryInterface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockParseStateFactory : public ParseStateFactoryInterface {

public:
    MOCK_METHOD(std::shared_ptr<ParseState>, getNextState, (), (override));
    MOCK_METHOD(std::shared_ptr<ParseState>, getFirstState, (), (override));
};


#endif //TODOLIST_MOCKPARSESTATEFACTORY_H
