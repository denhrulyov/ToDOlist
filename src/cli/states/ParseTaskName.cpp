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

std::shared_ptr<State> ParseTaskName::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input.empty()) {
        context.getIO().log("Task name must not be empty!");
        return std::make_shared<StartState>(nullptr);
    }
    context.getTaskBuffer().name_ = input;
    return next_state_;
}
