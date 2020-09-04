//
// Created by denis on 01.09.20.
//

#include "InputTaskStateMachine.h"
#include "ParseState.h"
#include "cli/state_machines/main/ConsoleContext.h"

InputTaskStateMachine::InputTaskStateMachine(
        const std::vector<std::shared_ptr<ParseState>> &state_sequence,
        ConsoleIOInterface& io)
:
state_sequence_(state_sequence),
context_(std::move(std::make_unique<InputTaskContext>(io)))
{}

typename InputTaskStateMachine::Result InputTaskStateMachine::run() {

    for (auto state : state_sequence_) {
        ParseState::Event event;
        do {
            state->print(*context_);
            event = state->execute(*context_);
            if (event == ParseState::Event::EXIT) {
                return Result::FAIL;
            }
        } while(event != ParseState::Event::SUCCESS);
    }
    return Result::SUCCESS;
}


TaskDTO InputTaskStateMachine::extractTask() {
    return TaskDTO::create( context_->getName().value(),
                            context_->getPriority().value(),
                            context_->getLabel().value(),
                            context_->getDate().value());
}
