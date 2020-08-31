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
    context.getIO().log("You specified task with following parameters:");
    context.getIO().log(std::string("name :     ") + field_repr(buffer.name_));
    context.getIO().log(std::string("priority : ") + field_repr(buffer.priority_));
    context.getIO().log(std::string("label :    ") + field_repr(buffer.label_));
    context.getIO().log(std::string("date :     ") + field_repr(buffer.date_));
    context.getIO().log("Y - accept, n - decline");
}


std::shared_ptr<State>
AddTaskState::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input != "Y") {
        context.getIO().log("aborting...");
        return std::make_shared<ParseCommand>();
    }
    if (!context.getTaskBuffer().filled()) {
        context.getIO().log("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().log("Task added successfully.");
    }
    return std::make_shared<ParseCommand>();
}

void AddTaskState::help(ConsoleContext &) {

}


