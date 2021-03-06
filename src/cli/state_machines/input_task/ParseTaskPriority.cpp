//
// Created by denis on 19.08.20.
//

#include "ParseTaskPriority.h"
#include "ParseState.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "InputTaskContext.h"


ParseTaskPriority::ParseTaskPriority() :
ParseState()
{}

void ParseTaskPriority::print(InputTaskContextInterface &context) {
    context.getIO().putLine("Task priority:");
}

ParseState::Event ParseTaskPriority::processInput(InputTaskContextInterface &context) {
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task priority must not be empty");
        return ParseState::Event::INCORRECT;
    }
    while (!input.empty() && input.back() == ' ') {
        input.pop_back();
    }
    for (auto &symbol : input) {
        symbol = std::tolower(symbol);
    }
           if (input == "first" || input == "1") {
               context.setPriority(TaskPriority::FIRST);
    } else if (input == "second" || input == "2") {
               context.setPriority(TaskPriority::SECOND);
    } else if (input == "third" || input == "3") {
               context.setPriority(TaskPriority::THIRD);
    } else if (input == "none" || input == "0") {
               context.setPriority(TaskPriority::NONE);
    } else {
               help(context);
               return ParseState::Event::INCORRECT;
    }
    return ParseState::Event::SUCCESS;
}

void ParseTaskPriority::help(InputTaskContextInterface &context) {
    context.getIO().putLine("Incorrect priority!");
    context.getIO().putLine("Possible : ");
    context.getIO().putLine("first    (1)");
    context.getIO().putLine("second   (2)");
    context.getIO().putLine("third    (3)");
    context.getIO().putLine("none     (0)");
}
