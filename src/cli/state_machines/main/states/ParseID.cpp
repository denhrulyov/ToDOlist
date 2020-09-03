//
// Created by denis on 18.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"
#include "ParseID.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/state_machines/main/TaskTableIO.h"
#include "ParseCommand.h"
#include "InputState.h"

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
    return std::make_shared<InputState<AddTaskState, ParseCommand>>(
            std::move(
            std::make_unique<InputTaskStateMachine>(
                    std::vector<std::shared_ptr<ParseState>> {
                            std::make_shared<ParseTaskName>(),
                            std::make_shared<ParseTaskPriority>(),
                            std::make_shared<ParseTaskLabel>(),
                            std::make_shared<ParseTaskDate>()
                    },
                    context
                    )
            )
    );
}

void ParseID::help(ConsoleContext &) {

}
