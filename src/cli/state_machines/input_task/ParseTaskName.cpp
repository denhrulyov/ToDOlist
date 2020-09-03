//
// Created by denis on 19.08.20.
//

#include "cli/states/ParseCommand.h"
#include "cli/states/StartState.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "cli/states/AddTaskState.h"
#include "cli/states/AddSubTaskState.h"
#include "cli/ConsoleContext.h"

ParseTaskName::ParseTaskName() :
ParseState()
{}

void ParseTaskName::print(InputTaskContext &context) {
    context.getIO().putLine("Task name:");
}

ParseState::Event ParseTaskName::execute(InputTaskContext &context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task name must not be empty!");
        return ParseState::Event::FAIL;
    }
    context.setName(input);
    return ParseState::Event::SUCCESS;
}

void ParseTaskName::help(InputTaskContext &) {

}