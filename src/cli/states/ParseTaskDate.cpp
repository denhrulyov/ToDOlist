//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "ParseTaskDate.h"
#include "StartState.h"



template<class T_next, class T_exit>
ParseTaskDate<T_next, T_exit>::ParseTaskDate(const std::shared_ptr<State>& next_state)
: ParseTask(next_state)
{}

template<class T_next, class T_exit>
void ParseTaskDate<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Date in format yyyy-mm-dd:");
}

template<class T_next, class T_exit>
void ParseTaskDate<T_next, T_exit>::execute(ConsoleContext& context) {

    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task date must not be empty!");
        next_state_ = std::make_shared<ParseTaskDate>(next_state_);
        return;
    }
    using namespace boost::gregorian;
    try {
        context.getTaskBuffer().date_ = BoostDate(from_string(input));
    } catch (...) {
        context.getIO().log("Incorrect date!");
        next_state_ = std::make_shared<ParseTaskDate>(next_state_);
    }

}

template<class T_next, class T_exit>
void ParseTaskDate<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskDate<
                    AddTaskState,
                    StartState>;
template class ParseTaskDate<
                    AddSubTaskState,
                    StartState>;
