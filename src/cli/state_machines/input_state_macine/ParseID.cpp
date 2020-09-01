//
// Created by denis on 18.08.20.
//

#include "cli/ConsoleContext.h"
#include "cli/states/DeleteTaskState.h"
#include "cli/states/ParseCommand.h"
#include "ParseID.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "cli/states/AddTaskState.h"
#include "cli/states/AddSubTaskState.h"
#include "cli/TaskTableIO.h"

ParseID::ParseID()
{}

void ParseID::print(ConsoleContext& context) {
    context.getIO().putLine("Input task number: ");
}

ParseState::Event ParseID::execute(ConsoleContext& context) {
    if (context.getTaskTable().empty()) {
        context.getIO().putLine("Task table is now empty. Make get command to gain some set of tasks.");
        return ParseState::Event::EXIT;
    }
    context.getIO().requestInputLine();
    std::string input = context.getIO().readRestBuffer();
    TaskNumber task_number = -1;
    try {
        task_number = std::stoi(input);
    } catch (...) {
        context.getIO().putLine("Incorrect number!");
        return ParseState::Event::FAIL;
    }
    if (task_number < 1 || task_number > (--context.getTaskTable().end())->first) {
        context.getIO().putLine("Index is out of table!");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return ParseState::Event::FAIL;
    }
    if (context.getTaskTable().count(task_number) == 0) {
        context.getIO().putLine("This task was deleted.");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return ParseState::Event::FAIL;
    }
    return ParseState::Event::SUCCESS;
}

void ParseID::help(ConsoleContext &) {

}
