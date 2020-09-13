//
// Created by denis on 11.09.20.
//

#include "InputSubTaskState.h"

std::shared_ptr<State> InputSubTaskState::getNextState(StateFactoryInterface &factory) {
    return factory.getInstanceOfAddSubTaskState();
}

std::shared_ptr<State> InputSubTaskState::getExitState(StateFactoryInterface &factory) {
    return factory.getInstanceOfParseCommand();
}

InputSubTaskState::InputSubTaskState(std::unique_ptr<InputTaskStateMachine> machine)
:
InputState(std::move(machine))
{}
