//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "cli/states/ParseCommand.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "cli/states/AddTaskState.h"
#include "cli/states/AddSubTaskState.h"


ParseTaskLabel::ParseTaskLabel()
{}

void ParseTaskLabel::print(InputTaskContext &context) {
    context.getIO().putLine("Label:");
}

ParseState::Event ParseTaskLabel::execute(InputTaskContext &context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task label must not be empty!");
        return ParseState::Event::FAIL;
    }
    context.setLabel(input);
    return ParseState::Event::SUCCESS;
}

void ParseTaskLabel::help(InputTaskContext &) {

}
