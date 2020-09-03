//
// Created by denis on 19.08.20.
//

#include "ParseTaskPriority.h"
#include "ParseState.h"
#include "cli/ConsoleContext.h"


ParseTaskPriority::ParseTaskPriority() :
ParseState()
{}

void ParseTaskPriority::print(ConsoleContext& context) {
    context.getIO().putLine("Task priority:");
}

ParseState::Event ParseTaskPriority::execute(ConsoleContext& context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task priority must not be empty");
        return ParseState::Event::FAIL;
    }
    for (auto &symbol : input) {
        symbol = std::tolower(symbol);
    }
           if (input == "first" || input == "1") {
               context.getTaskBuffer().priority_ = TaskPriority::FIRST;
    } else if (input == "second" || input == "2") {
               context.getTaskBuffer().priority_ = TaskPriority::SECOND;
    } else if (input == "third" || input == "3") {
               context.getTaskBuffer().priority_ = TaskPriority::THIRD;
    } else if (input == "none" || input == "0") {
               context.getTaskBuffer().priority_ = TaskPriority::NONE;
    } else {
               help(context);
               return ParseState::Event::FAIL;
    }
    return ParseState::Event::SUCCESS;
}

void ParseTaskPriority::help(ConsoleContext& context) {
    context.getIO().putLine("Incorrect priority!");
    context.getIO().putLine("Possible : ");
    context.getIO().putLine("first    (1)");
    context.getIO().putLine("second   (2)");
    context.getIO().putLine("third    (3)");
    context.getIO().putLine("none     (0)");
}
