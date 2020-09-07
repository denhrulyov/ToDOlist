//
// Created by denis on 20.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseTaskDate.h"
#include "InputTaskContext.h"


ParseTaskDate::ParseTaskDate()
{}

void ParseTaskDate::print(InputTaskContextInterface &context) {
    context.getIO().putLine("Date in format yyyy-mm-dd:");
}

ParseState::Event ParseTaskDate::execute(InputTaskContextInterface &context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task date must not be empty!");
        return ParseState::Event::FAIL;
    }
    using namespace boost::gregorian;
    try {
        context.setDate(BoostDate(from_string(input)));
    } catch (...) {
        context.getIO().putLine("Incorrect date!");
        return ParseState::Event::FAIL;
    }
    return ParseState::Event::SUCCESS;
}

void ParseTaskDate::help(InputTaskContextInterface &) {

}
