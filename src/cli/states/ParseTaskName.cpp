//
// Created by denis on 19.08.20.
//

#include "StartState.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "cli/ConsoleContext.h"

ParseTaskName::ParseTaskName(const std::shared_ptr<State>& next_state) :
ParseTask(next_state)
{}

void ParseTaskName::print(ConsoleContext& context) {
    context.getIO().log("Task name:");
}

void ParseTaskName::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task name must not be empty!");
        next_state_ = std::make_shared<ParseTaskName>(next_state_);
        return;
    }
    context.getTaskBuffer().name_ = input;

}

void ParseTaskName::help(ConsoleContext &) {

}
