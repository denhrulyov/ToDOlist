//
// Created by denis on 20.08.20.
//

#include "AddTaskState.h"

//
// Created by denis on 18.08.20.
//

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "ParseCommand.h"
#include "cli/ConsoleContext.h"
#include "cli/states/utils/Utils.h"




AddTaskState::AddTaskState()
:
State()
{}

void
AddTaskState::print(ConsoleContext& context) {
    auto& buffer = context.getTaskBuffer();
    context.getIO().putLine("You specified task with following parameters:");
    context.getIO().putLine(std::string("name :     ") + field_repr(buffer.name_));
    context.getIO().putLine(std::string("priority : ") + field_repr(buffer.priority_));
    context.getIO().putLine(std::string("label :    ") + field_repr(buffer.label_));
    context.getIO().putLine(std::string("date :     ") + field_repr(buffer.date_));
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
    if (!context.getTaskBuffer().filled()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().putLine("Task added successfully.");
    }
    return std::make_shared<ParseCommand>();
}

void AddTaskState::help(ConsoleContext &) {

}


