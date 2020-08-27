//
// Created by denis on 18.08.20.
//

#include "cli/ConsoleContext.h"
#include "StartState.h"
#include "ParseID.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/TaskTableIO.h"

template<class T_next, class T_exit>
ParseID<T_next, T_exit>::ParseID(const std::shared_ptr<State>& next_state)
: ParseState(next_state)
{}

template<class T_next, class T_exit>
void ParseID<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Input task number: ");
}

template<class T_next, class T_exit>
void ParseID<T_next, T_exit>::execute(ConsoleContext& context) {
    if (context.getTaskTable().empty()) {
        context.getIO().log("Task table is now empty. Make get command to gain some set of tasks.");
        next_state_ = std::make_shared<StartState>(nullptr);
        return;
    }
    std::string input = context.getIO().readLine();
    TaskNumber task_number = -1;
    try {
        task_number = std::stoi(input);
    } catch (...) {
        context.getIO().log("Incorrect number!");
        next_state_ = std::make_shared<ParseID>(nullptr);
        return;
    }
    if (task_number < 1 || task_number > (--context.getTaskTable().end())->first) {
        context.getIO().log("Index is out of table!");
        context.getIO().log("Current table is:");
        task_table_io::print(context);
        next_state_ = std::make_shared<ParseID>(nullptr);
        return;
    }
    if (context.getTaskTable().count(task_number) == 0) {
        context.getIO().log("This task was deleted.");
        context.getIO().log("Current table is:");
        task_table_io::print(context);
        next_state_ = std::make_shared<ParseID>(nullptr);
    }

}

template<class T_next, class T_exit>
void ParseID<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseID<
                    ParseTaskName<
                        ParseTaskPriority<
                            ParseTaskLabel<
                                ParseTaskDate<
                                    AddTaskState,
                                    StartState>,
                                StartState>,
                            StartState>,
                        StartState>,
                    StartState>;
