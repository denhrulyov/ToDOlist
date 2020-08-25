//
// Created by denis on 25.08.20.
//

#include "State.h"
#include "cli/ConsoleContext.h"

State::State(const std::shared_ptr<State>& next_state)
: next_state_(next_state) {};

std::shared_ptr<State> State::switchState(ConsoleContext& context) {
    return next_state_;
}