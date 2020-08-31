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
    auto& buffer = context.getTaskBuffer();
    context.getIO().log("Main task: ");
    context.getIO().log(std::string("name :     ") + field_repr(buffer.name_));
    context.getIO().log(std::string("priority : ") + field_repr(buffer.priority_));
    context.getIO().log(std::string("label :    ") + field_repr(buffer.label_));
    context.getIO().log(std::string("date :     ") + field_repr(buffer.date_));
    context.getIO().log("You specified subtask with following parameters:");
    context.getIO().log(std::string("name :     ") + field_repr(buffer.name_));
    context.getIO().log(std::string("priority : ") + field_repr(buffer.priority_));
    context.getIO().log(std::string("label :    ") + field_repr(buffer.label_));
    context.getIO().log(std::string("date :     ") + field_repr(buffer.date_));
    context.getIO().log("Y - accept, n - decline");
}


std::shared_ptr<State>
AddSubTaskState::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input != "Y") {
        context.getIO().log("aborting...");
        return std::make_shared<StartState>();
    }
    if (!context.getTaskBuffer().filled()) {
        context.getIO().log("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().log("Task added successfully.");
    }
    return std::make_shared<StartState>();
}

void AddSubTaskState::help(ConsoleContext &) {

}
