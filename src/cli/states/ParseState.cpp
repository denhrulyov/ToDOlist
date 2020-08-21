//
// Created by denis on 18.08.20.
//

#include "ParseState.h"

ParseState::ParseState(const std::shared_ptr<State>& next_state)
: State(next_state)
{}
