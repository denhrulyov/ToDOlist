//
// Created by denis on 14.09.20.
//

#ifndef TODOLIST_MOCKINPUTTASKCONTEXT_H
#define TODOLIST_MOCKINPUTTASKCONTEXT_H


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cli/state_machines/input_task/InputTaskContextInterface.h"

class MockInputTaskContext : public InputTaskContextInterface {

public:
    MOCK_METHOD(ConsoleIOInterface&, getIO, (), (override, const));
    MOCK_METHOD(std::optional<std::string>  , getName, (), (const, override));
    MOCK_METHOD(std::optional<TaskPriority> , getPriority, (), (const, override));
    MOCK_METHOD(std::optional<std::string>  , getLabel, (), (const, override));
    MOCK_METHOD(std::optional<BoostDate>    , getDate, (), (const, override));
    MOCK_METHOD(void, setName, (const std::optional<std::string> &), (override));
    MOCK_METHOD(void, setPriority, (const std::optional<TaskPriority> &), (override));
    MOCK_METHOD(void, setLabel, (const std::optional<std::string> &), (override));
    MOCK_METHOD(void, setDate, (const std::optional<BoostDate> &), (override));
};


#endif //TODOLIST_MOCKINPUTTASKCONTEXT_H
