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

std::shared_ptr<State> ParseTaskDate::execute(ConsoleContext& context) {

    std::string input = context.getIO().read();
    if (input.empty()) {
        context.getIO().log("Task date must not be empty!");
        return std::make_shared<StartState>(nullptr);
    }
    using namespace boost::gregorian;
    try {
        context.getTaskBuffer().date_ = BoostDate(from_string(input));
    } catch (...) {
        context.getIO().log("Incorrect date!");
        return std::make_shared<StartState>(nullptr);
    }
    return next_state_;
}