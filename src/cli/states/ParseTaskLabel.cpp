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

void ParseTaskLabel::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task label must not be empty!");
        next_state_ = std::make_shared<ParseTaskLabel>(next_state_);
        return;
    }
    context.getTaskBuffer().label_ = input;

}

void ParseTaskLabel::help(ConsoleContext &) {

}


