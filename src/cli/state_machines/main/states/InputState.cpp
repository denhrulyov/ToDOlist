//
// Created by denis on 11.09.20.
//

#include "InputState.h"

std::optional<TaskDTO> convert_input(const InputTaskContextInterface& input) {
    if (input.getName() &&
        input.getPriority() &&
        input.getLabel() &&
        input.getDate()) {
        return TaskDTO::create(
                input.getName().value(),
                input.getPriority().value(),
                input.getLabel().value(),
                input.getDate().value()
        );
    }
    return std::nullopt;

}

std::shared_ptr<State> InputState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().clear();
    std::optional<TaskDTO> possible_task;
    switch (machine_->run()) {
        case InputTaskStateMachine::Result::SUCCESS:
            possible_task = convert_input(machine_->getContext());
            if (!possible_task) {
                return getExitState(factory);
            }
            context.fillTaskBuffer(possible_task.value());
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