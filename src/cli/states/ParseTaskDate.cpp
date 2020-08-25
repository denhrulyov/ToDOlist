//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "AddTaskState.h"
#include "ParseTaskDate.h"
#include "StartState.h"

ParseTaskDate::ParseTaskDate(const std::shared_ptr<State>& next_state)
: ParseTask(next_state)
{}

void ParseTaskDate::print(ConsoleContext& context) {
    context.getIO().log("Date in format yyyy-mm-dd:");
}

void ParseTaskDate::execute(ConsoleContext& context) {

    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task date must not be empty!");
        next_state_ = std::make_shared<ParseTaskDate>(next_state_);
        return;
    }
    using namespace boost::gregorian;
    try {
        context.getTaskBuffer().date_ = BoostDate(from_string(input));
    } catch (...) {
        context.getIO().log("Incorrect date!");
        next_state_ = std::make_shared<ParseTaskDate>(next_state_);
    }

}

void ParseTaskDate::help(ConsoleContext &) {

}
