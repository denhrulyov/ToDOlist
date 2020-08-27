//
// Created by denis on 19.08.20.
//

#include "StartState.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/ConsoleContext.h"

template<class T_next, class T_exit>
ParseTaskName<T_next, T_exit>::ParseTaskName(const std::shared_ptr<State>& next_state) :
ParseTask(next_state)
{}

template<class T_next, class T_exit>
void ParseTaskName<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Task name:");
}

template<class T_next, class T_exit>
void ParseTaskName<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task name must not be empty!");
        next_state_ = std::make_shared<ParseTaskName>(next_state_);
        return;
    }
    context.getTaskBuffer().name_ = input;

}

template<class T_next, class T_exit>
void ParseTaskName<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskName<
                    ParseTaskPriority<
                            ParseTaskLabel<
                                ParseTaskDate<
                                    AddTaskState,
                                    StartState>,
                                StartState>,
                            StartState>,
                    StartState>;


template class ParseTaskName<
                    ParseTaskPriority<
                            ParseTaskLabel<
                                    ParseTaskDate<
                                            AddSubTaskState,
                                            StartState>,
                                    StartState>,
                            StartState>,
                    StartState>;