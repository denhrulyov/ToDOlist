//
// Created by denis on 19.08.20.
//

#include "ParseCommand.h"
#include "StartState.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/ConsoleContext.h"

template<class T_next, class T_exit>
ParseTaskName<T_next, T_exit>::ParseTaskName() :
ParseTask()
{}

template<class T_next, class T_exit>
void ParseTaskName<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Task name:");
}

template<class T_next, class T_exit>
std::shared_ptr<State> ParseTaskName<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task name must not be empty!");
        return std::make_shared<ParseTaskName>();
    }
    context.getTaskBuffer().name_ = input;
    return std::make_shared<T_next>();
}

template<class T_next, class T_exit>
void ParseTaskName<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskName<
                    ParseTaskPriority<
                            ParseTaskLabel<
                                ParseTaskDate<
                                    AddTaskState,
                                    ParseCommand>,
                                ParseCommand>,
                        ParseCommand>,
                    ParseCommand>;


template class ParseTaskName<
                    ParseTaskPriority<
                            ParseTaskLabel<
                                    ParseTaskDate<
                                            AddSubTaskState,
                                            ParseCommand>,
                                    ParseCommand>,
                            ParseCommand>,
                    ParseCommand>;