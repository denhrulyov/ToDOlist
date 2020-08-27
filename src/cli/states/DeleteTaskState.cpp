//
// Created by denis on 26.08.20.
//

#include "cli/ConsoleContext.h"
#include "DeleteTaskState.h"

DeleteTaskState::DeleteTaskState(const std::shared_ptr<State> &next_state)
: State(next_state)
{}

void DeleteTaskState::print(ConsoleContext &context) {
    context.getIO().log("You want to delete task: ");
    // 1. get task from context.getService().getTaskByID()
    // 2. print task fields

}


void DeleteTaskState::execute(ConsoleContext &context) {

}

void DeleteTaskState::help(ConsoleContext &context) {

}
