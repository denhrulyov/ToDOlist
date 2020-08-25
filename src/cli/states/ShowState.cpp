//
// Created by denis on 25.08.20.
//

#include "ShowState.h"
#include "StartState.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"
#include "cli/ConsoleContext.h"
#include "Utils.h"

ShowState::ShowState(const std::shared_ptr<State> &next_state) :
State(next_state)
{}

void ShowState::print(ConsoleContext &context) {

}

void ShowState::execute(ConsoleContext &context) {
    next_state_ = std::make_shared<ParseCommand>(nullptr);
    if (context.getIO().isEmpty()) {
        context.getIO().log("No show option specified!");
        help(context);
        return;
    }
    std::string input = context.getIO().read();
    if (input.empty()) {
        context.getIO().log("Argument line is empty!");
        return;
    }
    if (input == "today") {
        context.getIO().log("Tasks for today:");
    } else if (input == "this_week") {
        context.getIO().log("Tasks for this week:");
    } else if (input == "all") {
        context.getIO().log("All tasks:");
    } else if (input == "tag") {
        next_state_ = std::make_shared<ParseShowTag>(nullptr);
    }
    else if (input == "current_list") {
        context.getIO().log("Active list of tasks:");
    } else {
        context.getIO().log("Incorrect show options!");
        help(context);
    }
}

void ShowState::help(ConsoleContext& context) {
    context.getIO().log("Available options:");
    context.getIO().log("-  today");
    context.getIO().log("-  this_week");
    context.getIO().log("-  all");
    context.getIO().log("-  tag <tg>, where <tg> is a desired label");
}

