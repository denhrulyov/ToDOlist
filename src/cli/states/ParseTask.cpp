//
// Created by denis on 18.08.20.
//

#include "ParseTask.h"
#include "cli/ConsoleContext.h"

ParseTask::ParseTask(const std::shared_ptr<State>& next_state)
:
ParseState(next_state)
{}

