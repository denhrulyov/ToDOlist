//
// Created by denis on 20.08.20.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::run() {
    while (current_state_) {
        current_state_->print(*context_);
        current_state_ = current_state_->execute(*context_, *factory_);
    }
}

ConsoleStateMachine::ConsoleStateMachine(std::unique_ptr<ConsoleContextInterface> context,
                                         std::unique_ptr<StateFactoryInterface> factory,
                                         const std::shared_ptr<State>& start_state)
:
context_(std::move(context)),
factory_(std::move(factory)),
current_state_(start_state)
{}
