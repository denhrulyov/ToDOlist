//
// Created by denis on 03.09.20.
//
#include "DeleteStateParseID.h"

#include "cli/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"
#include "AddTaskState.h"
#include "InputState.h"
#include "DeleteTaskState.h"
#include "cli/TaskTableIO.h"


DeleteStateParseID::DeleteStateParseID()
: State()
{}

void DeleteStateParseID::print(ConsoleContext& context) {
    context.getIO().putLine("Input task number: ");
}

std::shared_ptr<State> DeleteStateParseID::execute(ConsoleContext& context) {
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
    return std::make_shared<DeleteTaskState>();
}

void DeleteStateParseID::help(ConsoleContext &) {

}
