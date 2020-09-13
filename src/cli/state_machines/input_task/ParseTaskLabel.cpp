//
// Created by denis on 20.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"


ParseTaskLabel::ParseTaskLabel()
{}

void ParseTaskLabel::print(InputTaskContextInterface &context) {
    context.getIO().putLine("Label:");
}

ParseState::Event ParseTaskLabel::processInput(InputTaskContextInterface &context) {
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task label must not be empty!");
        return ParseState::Event::FAIL;
    }
    context.setLabel(input);
    return ParseState::Event::SUCCESS;
}

void ParseTaskLabel::help(InputTaskContextInterface &) {

}
