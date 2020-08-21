//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "StartState.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"

ParseTaskLabel::ParseTaskLabel(const std::shared_ptr<State>& next_state)
: ParseTask(next_state)
{}

void ParseTaskLabel::print(ConsoleContext& context) {
    context.getIO().log("Label:");
}

std::shared_ptr<State> ParseTaskLabel::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input.empty()) {
        context.getIO().log("Task label must not be empty!");
        return std::make_shared<StartState>(nullptr);
    }
    context.getTaskBuffer().label_ = input;
    return next_state_;
}


