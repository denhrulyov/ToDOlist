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

void ParseID::print(ConsoleContextInterface &context) {
    context.getIO().putLine("Input task number: ");
}

std::shared_ptr<State> ParseID::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getMatchingTablePositionToID().empty()) {
        context.getIO().putLine("Task table is now empty. Make get command to gain some set of tasks.");
        return factory.getInstanceOfParseCommand();
    }
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    std::string input = context.getIO().readRestBuffer();
    TaskNumber task_number = 0;
    try {
        task_number = std::stoi(input);
    } catch (...) {
        context.getIO().putLine("Incorrect number!");
        return factory.getInstanceOfParseCommand();
    }
    TaskNumber max_row_number = (--context.getMatchingTablePositionToID().end())->first;
    if (task_number < 1 || task_number > max_row_number) {
        context.getIO().putLine("Index is out of table!");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return factory.getInstanceOfParseCommand();
    }
    if (context.getMatchingTablePositionToID().count(task_number) == 0) {
        context.getIO().putLine("This task was deleted.");
        context.getIO().putLine("Current table is:");
        task_table_io::print(context);
        return factory.getInstanceOfParseCommand();
    }
    context.fillIDBuffer(context.getMatchingTablePositionToID()[task_number]);
    return switchGood(context, factory);
}

void ParseID::help(ConsoleContextInterface &) {

}
