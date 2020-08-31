//
// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "ParseID.h"
#include "DeleteTaskState.h"
#include "cli/states/utils/Utils.h"

ParseCommand::ParseCommand()
: ParseState()
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().log("Input command to execute");;
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context) {
    context.getIO().clear();
    std::string input = context.getIO().read();
    if (input == "add") {
        return std::make_shared<ParseAddType>();
    }
    else if (input == "show") {
        return std::make_shared<ShowState>();
    } else if (input == "delete") {
        return std::make_shared<InputChain<pack<ParseID>, DeleteTaskState, ParseCommand>>();
    } else {
        context.getIO().log("Unknown command!");
        help(context);
        context.getIO().clear();
        return std::make_shared<ParseCommand>();
    }
}

void ParseCommand::help(ConsoleContext &context) {
    context.getIO().log("Available commands:");
    context.getIO().log("-  add");
    context.getIO().log("-  show");
    context.getIO().log("-  postpone");
    context.getIO().log("-  delete");
}
