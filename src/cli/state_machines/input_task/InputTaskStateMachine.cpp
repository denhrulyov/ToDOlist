//
// Created by denis on 01.09.20.
//


#include "InputTaskStateMachine.h"
#include "ParseState.h"
#include "cli/state_machines/main/ConsoleContext.h"

InputTaskStateMachine::InputTaskStateMachine(
        std::unique_ptr<ParseStateFactoryInterface> factory,
        std::unique_ptr<InputTaskContextInterface> context)
:
factory_(std::move(factory)),
context_(std::move(context))
{}

InputTaskStateMachine::Result InputTaskStateMachine::run() {
    auto state = factory_->getNextState();
    while (state) {
        ParseState::Event event;
        do {
            state->print(*context_);
            event = state->execute(*context_);
            switch (event) {
                case ParseState::Event::ABORT:
                    return Result::FAIL;
                case ParseState::Event::EXIT:
                    return Result::EXIT_PROGRAM;
                default:
                    break;
            }
        } while(event != ParseState::Event::SUCCESS);
        state = factory_->getNextState();
    }
    return Result::SUCCESS;
}


TaskDTO InputTaskStateMachine::extractTask() {
    return TaskDTO::create( context_->getName().value(),
                            context_->getPriority().value(),
                            context_->getLabel().value(),
                            context_->getDate().value());
}
