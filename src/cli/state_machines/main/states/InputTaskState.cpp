//
// Created by denis on 11.09.20.
//

#include "InputTaskState.h"
#include "AddTaskState.h"
#include "ParseCommand.h"

std::shared_ptr<State> InputTaskState::getNextState(StateFactoryInterface &factory) {
    return factory.getInstanceOfAddTaskState();
}

std::shared_ptr<State> InputTaskState::getExitState(StateFactoryInterface &factory) {
    return factory.getInstanceOfParseCommand();
}

InputTaskState::InputTaskState(std::unique_ptr<InputTaskStateMachine> machine)
:
InputState(std::move(machine))
{}
