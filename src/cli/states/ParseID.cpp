//
// Created by denis on 18.08.20.
//

#include "cli/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"
#include "ParseID.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/TaskTableIO.h"

template<class T_next, class T_exit>
ParseID<T_next, T_exit>::ParseID()
: ParseTask()
{}

template<class T_next, class T_exit>
void ParseID<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Input task number: ");
}

template<class T_next, class T_exit>
std::shared_ptr<State> ParseID<T_next, T_exit>::execute(ConsoleContext& context) {
    if (context.getTaskTable().empty()) {
        context.getIO().log("Task table is now empty. Make get command to gain some set of tasks.");
        return std::make_shared<T_exit>();
    }
    context.getIO().requestInputLine();
    std::string input = tokenizer_->read(context.getIO()).getData().value();
    TaskNumber task_number = -1;
    try {
        task_number = std::stoi(input);
    } catch (...) {
        context.getIO().log("Incorrect number!");
        return std::make_shared<ParseID>();
    }
    if (task_number < 1 || task_number > (--context.getTaskTable().end())->first) {
        context.getIO().log("Index is out of table!");
        context.getIO().log("Current table is:");
        task_table_io::print(context);
        return std::make_shared<ParseID>();
    }
    if (context.getTaskTable().count(task_number) == 0) {
        context.getIO().log("This task was deleted.");
        context.getIO().log("Current table is:");
        task_table_io::print(context);
        return std::make_shared<ParseID>();
    }
    return std::make_shared<T_next>();
}

template<class T_next, class T_exit>
void ParseID<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseID<
                    ParseTaskName<
                        ParseTaskPriority<
                            ParseTaskLabel<
                                ParseTaskDate<
                                    AddSubTaskState,
                                        ParseCommand>,
                                    ParseCommand>,
                                ParseCommand>,
                            ParseCommand>,
                    ParseCommand>;

template class ParseID<DeleteTaskState, ParseCommand>;