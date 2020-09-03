//
// Created by denis on 20.08.20.
//

#include "AddTaskState.h"

//
// Created by denis on 18.08.20.
//

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "ParseCommand.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/states/utils/Utils.h"




AddTaskState::AddTaskState()
:
State()
{}

void
AddTaskState::print(ConsoleContext& context) {
    auto dto = context.getTaskBuffer().value();
    context.getIO().putLine("You specified task with following parameters:");
    context.getIO().putLine(std::string("name :     ")
                                                + field_repr(dto.getName()));
    context.getIO().putLine(std::string("priority : ")
                                                + field_repr(dto.getPriority()));
    context.getIO().putLine(std::string("label :    ")
                                                + field_repr(dto.getLabel()));
    context.getIO().putLine(std::string("date :     ")
                                                + field_repr(std::optional(dto.getDate())));
    context.getIO().putLine("Y - accept, n - decline");
}


std::shared_ptr<State>
AddTaskState::execute(ConsoleContext& context) {
    context.getIO().requestInputLine();
    std::string input = context.getIO().readWord();
    if (input != "Y") {
        context.getIO().putLine("aborting...");
        return std::make_shared<ParseCommand>();
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().putLine("Task added successfully.");
    }
    return std::make_shared<ParseCommand>();
}

void AddTaskState::help(ConsoleContext &) {

}


