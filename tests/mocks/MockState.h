//
// Created by denis on 10.09.20.
//

#ifndef TODOLIST_MOCKSTATE_H
#define TODOLIST_MOCKSTATE_H

#include "cli/state_machines/main/states/State.h"

class MockState : public State {

public:
    MOCK_METHOD(void, print, (ConsoleContextInterface&), (override));
    MOCK_METHOD(std::shared_ptr<State>, execute, (ConsoleContextInterface&, StateFactoryInterface&), (override));
    MOCK_METHOD(void, help, (ConsoleContextInterface&), (override));

};


#endif //TODOLIST_MOCKSTATE_H
