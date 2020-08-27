//
// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "ParseID.h"
#include "DeleteTaskState.h"
#include "Utils.h"

ParseCommand::ParseCommand(const std::shared_ptr<State> & next_state)
: ParseState(next_state)
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().log("Input command to execute");;
}

void ParseCommand::execute(ConsoleContext &context) {
    context.getIO().clear();
    std::string input = context.getIO().read();
    if (input == "add") {
        next_state_ = std::make_shared<ParseAddType>(nullptr);
    }
    else if (input == "show") {
        next_state_ = std::make_shared<ShowState>(nullptr);
    } else if (input == "delete") {
        next_state_ = create_chain<ParseID, DeleteTaskState>();
    } else {
        context.getIO().log("Unknown command!");
        help(context);
        context.getIO().clear();
        next_state_ = std::make_shared<ParseCommand>(nullptr);
    }
}

void ParseCommand::help(ConsoleContext &context) {
    context.getIO().log("Available commands:");
    context.getIO().log("-  add");
    context.getIO().log("-  show");
    context.getIO().log("-  postpone");
    context.getIO().log("-  delete");
}
