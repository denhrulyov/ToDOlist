//
// Created by denis on 19.08.20.
//

#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "cli/state_machines/main/ConsoleContext.h"

ParseTaskName::ParseTaskName() :
ParseState()
{}

void ParseTaskName::print(InputTaskContextInterface &context) {
    context.getIO().putLine("Task name:");
}

ParseState::Event ParseTaskName::processInput(InputTaskContextInterface &context) {
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task name must not be empty!");
        return ParseState::Event::INCORRECT;
    }
    context.setName(input);
    return ParseState::Event::SUCCESS;
}

void ParseTaskName::help(InputTaskContextInterface &) {

}