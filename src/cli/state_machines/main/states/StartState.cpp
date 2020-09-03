//
// Created by denis on 18.08.20.
//

#include "StartState.h"
#include "ParseCommand.h"
#include "cli/state_machines/main/ConsoleContext.h"

StartState::StartState()
{}


std::shared_ptr<State>
StartState::execute(ConsoleContext& context) {
    return std::make_shared<ParseCommand>();
}

void
StartState::print(ConsoleContext& context) {
    context.getIO().putLine("Welcome to TODO list CLI.");
    help(context);
}

void StartState::help(ConsoleContext& context) {
    context.getIO().putLine("   Type  ");
    context.getIO().putLine("|   __help__  to get see available options");
    context.getIO().putLine("|   __abort__  to abort executing current command");
    context.getIO().putLine("|   __exit__  to exit");
    context.getIO().putLine("THESE WORDS ARE RESERVED ");
    context.getIO().putLine("AND MUST NOT BE A PART OF PARAMETER!");
}

