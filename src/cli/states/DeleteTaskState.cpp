//
// Created by denis on 26.08.20.
//

#include "cli/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"

DeleteTaskState::DeleteTaskState()
: State()
{}

void DeleteTaskState::print(ConsoleContext &context) {
    context.getIO().log("You want to delete task: ");
    // 1. get task from context.getService().getTaskByID()
    // 2. print task fields

}


std::shared_ptr<State> DeleteTaskState::execute(ConsoleContext &context) {
    return std::make_shared<ParseCommand>();
}

void DeleteTaskState::help(ConsoleContext &context) {

}
