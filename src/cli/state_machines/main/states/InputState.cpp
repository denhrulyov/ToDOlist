//
// Created by denis on 11.09.20.
//

#include "InputState.h"

std::shared_ptr<State> InputState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().clear();
    switch (machine_->run()) {
        case InputTaskStateMachine::Result::SUCCESS:
            context.fillTaskBuffer(machine_->extractTask());
            return getNextState(factory);
        case InputTaskStateMachine::Result::FAIL:
            return getExitState(factory);
        default:
            return nullptr;
    }
}

void InputState::print(ConsoleContextInterface &) {

}

void InputState::help(ConsoleContextInterface &) {

}

InputState::InputState(std::unique_ptr<InputTaskStateMachine> machine)
        :
        machine_(std::move(machine))
{}