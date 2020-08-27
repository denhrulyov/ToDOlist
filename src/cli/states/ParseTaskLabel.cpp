//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "StartState.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"

template<class T_next, class T_exit>
ParseTaskLabel<T_next, T_exit>::ParseTaskLabel(const std::shared_ptr<State>& next_state)
: ParseTask(next_state)
{}

template<class T_next, class T_exit>
void ParseTaskLabel<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Label:");
}

template<class T_next, class T_exit>
void ParseTaskLabel<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task label must not be empty!");
        next_state_ = std::make_shared<ParseTaskLabel>(next_state_);
        return;
    }
    context.getTaskBuffer().label_ = input;

}

template<class T_next, class T_exit>
void ParseTaskLabel<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskLabel<
                    ParseTaskDate<
                            AddTaskState,
                            StartState>,
                    StartState>;

template class ParseTaskLabel<
                    ParseTaskDate<
                            AddSubTaskState,
                            StartState>,
                    StartState>;