//
// Created by denis on 18.08.20.
//

#include "StartState.h"
#include "ParseCommand.h"
#include "cli/ConsoleContext.h"

StartState::StartState(const std::shared_ptr<State>& next_state)
:
State(next_state)
{}


void
StartState::execute(ConsoleContext& context) {
    next_state_ = std::make_shared<ParseCommand>(nullptr);
}

void
StartState::print(ConsoleContext& context) {
    context.getIO().log("Welcome to TODO list CLI.");
    help(context);
}

void StartState::help(ConsoleContext& context) {
    context.getIO().log("   Type  ");
    context.getIO().log("|   __help__  to get see available options");
    context.getIO().log("|   __abort__  to abort executing current command");
    context.getIO().log("|   __exit__  to exit");
    context.getIO().log("THESE WORDS ARE RESERVED ");
    context.getIO().log("AND MUST NOT BE A PART OF PARAMETER!");
}

