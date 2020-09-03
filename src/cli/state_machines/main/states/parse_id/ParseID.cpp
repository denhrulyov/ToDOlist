//
// Created by denis on 18.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/states/DeleteTaskState.h"
#include "cli/state_machines/main/states/ParseCommand.h"
#include "ParseID.h"
#include "cli/state_machines/main/states/AddTaskState.h"
#include "cli/state_machines/main/states/AddSubTaskState.h"
#include "cli/state_machines/main/TaskTableIO.h"
#include "cli/state_machines/main/states/ParseCommand.h"
#include "cli/state_machines/main/states/InputState.h"

ParseID::ParseID()
{}

void ParseID::print(ConsoleContext& context) {
    context.getIO().putLine("Input task number: ");
}

std::shared_ptr<State> ParseID::execute(ConsoleContext& context) {
    if (context.getTaskTable().empty()) {
        context.getIO().putLine("Task table is now empty. Make get command to gain some set of tasks.");
        return std::make_shared<ParseCommand>();
    }
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    TaskNumber task_number = -1;
    try {
        task_number = std::stoi(input);
    } catch (...) {
        context.getIO().putLine("Incorrect number!");
        return std::make_shared<ParseCommand>();
    }
    if (task_number < 1 || task_number > (--context.getTaskTable().end())->first) {
        context.getIO().putLine("Index is out of table!");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return std::make_shared<ParseCommand>();
    }
    if (context.getTaskTable().count(task_number) == 0) {
        context.getIO().putLine("This task was deleted.");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return std::make_shared<ParseCommand>();
    }
    return switchGood(context);
}

void ParseID::help(ConsoleContext &) {

}
