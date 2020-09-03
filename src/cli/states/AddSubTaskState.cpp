//
// Created by denis on 21.08.20.
//

#include "AddSubTaskState.h"

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "StartState.h"
#include "cli/ConsoleContext.h"
#include "cli/states/utils/Utils.h"


AddSubTaskState::AddSubTaskState()
        :
        State()
{}

void
AddSubTaskState::print(ConsoleContext& context) {
    auto buffer = context.getTaskBuffer();
    context.getIO().putLine("Main task: ");
    context.getIO().putLine(std::string("name :     ") + field_repr(buffer->getName()));
    context.getIO().putLine(std::string("priority : ") + field_repr(buffer->getPriority()));
    context.getIO().putLine(std::string("label :    ") + field_repr(buffer->getLabel()));
    context.getIO().putLine(std::string("date :     ") + field_repr(std::optional(buffer->getDate())));
    context.getIO().putLine("You specified subtask with following parameters:");
    context.getIO().putLine(std::string("name :     ") + field_repr(buffer->getName()));
    context.getIO().putLine(std::string("priority : ") + field_repr(buffer->getPriority()));
    context.getIO().putLine(std::string("label :    ") + field_repr(buffer->getLabel()));
    context.getIO().putLine(std::string("date :     ") + field_repr(std::optional(buffer->getDate())));
    context.getIO().putLine("Y - accept, n - decline");
}


std::shared_ptr<State>
AddSubTaskState::execute(ConsoleContext& context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readWord();
    if (input != "Y") {
        context.getIO().putLine("aborting...");
        return std::make_shared<StartState>();
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().putLine("Task added successfully.");
    }
    return std::make_shared<StartState>();
}

void AddSubTaskState::help(ConsoleContext &) {

}
