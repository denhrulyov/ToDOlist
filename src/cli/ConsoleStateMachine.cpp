//
// Created by denis on 20.08.20.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::run() {
    while (current_state_) {
        current_state_->print(*context_);
        current_state_->execute(*context_);
        current_state_ = current_state_->switchState(*context_);
    }
}

ConsoleStateMachine::ConsoleStateMachine(std::unique_ptr<ConsoleContext> context,
                                         const std::shared_ptr<State>& start_state)
:
context_(std::move(context)),
current_state_(start_state)
{}
