//
// Created by denis on 25.08.20.
//

#include "ShowState.h"
#include "StartState.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"
#include "cli/ConsoleContext.h"

ShowState::ShowState() :
State()
{}

void ShowState::print(ConsoleContext &context) {

}

std::shared_ptr<State> ShowState::execute(ConsoleContext &context) {
    if (context.getIO().isEmpty()) {
        context.getIO().log("No show option specified!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
    std::string input = context.getIO().read();
    if (input.empty()) {
        context.getIO().log("Argument line is empty!");
    }
    if (input == "today") {
        context.getIO().log("Tasks for today:");
    } else if (input == "this_week") {
        context.getIO().log("Tasks for this week:");
    } else if (input == "all") {
        context.getIO().log("All tasks:");
    } else if (input == "tag") {
        return std::make_shared<ParseShowTag>();
    }
    else if (input == "current_list") {
        context.getIO().log("Active list of tasks:");
    } else {
        context.getIO().log("Incorrect show options!");
        help(context);
    }
    return std::make_shared<ParseCommand>();
}

void ShowState::help(ConsoleContext& context) {
    context.getIO().log("Available options:");
    context.getIO().log("-  today");
    context.getIO().log("-  this_week");
    context.getIO().log("-  all");
    context.getIO().log("-  tag <tg>, where <tg> is a desired label");
}

