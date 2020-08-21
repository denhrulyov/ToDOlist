//
// Created by denis on 18.08.20.
//

#include "StartState.h"
#include "ParseAddType.h"
#include "cli/ConsoleContext.h"

StartState::StartState(const std::shared_ptr<State>& next_state)
:
State(next_state)
{}


std::shared_ptr<State>
StartState::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input == "add") {
        return std::make_shared<ParseAddType>(nullptr);
    } else {
        context.getIO().log("Unknown command!");
        return std::make_shared<StartState>(nullptr);
    }
}

void
StartState::print(ConsoleContext& context) {
    context.getIO().log("Input command to execute");
}

