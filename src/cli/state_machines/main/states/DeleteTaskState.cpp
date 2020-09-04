//
// Created by denis on 26.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"

DeleteTaskState::DeleteTaskState()
: State()
{}

void DeleteTaskState::print(ConsoleContextInterface &context) {
    context.getIO().putLine("You want to delete task: ");
    // 1. get task from context.getService().getTaskByID()
    // 2. print task fields

}


std::shared_ptr<State> DeleteTaskState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().clear();
    return Visitor<ParseCommand>().visit(factory);
}

void DeleteTaskState::help(ConsoleContextInterface &context) {

}
