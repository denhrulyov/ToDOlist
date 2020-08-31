//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "ParseTaskDate.h"
#include "ParseCommand.h"


template<class T_next, class T_exit>
ParseTaskDate<T_next, T_exit>::ParseTaskDate()
: ParseTask()
{}

template<class T_next, class T_exit>
void ParseTaskDate<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Date in format yyyy-mm-dd:");
}

template<class T_next, class T_exit>
std::shared_ptr<State> ParseTaskDate<T_next, T_exit>::execute(ConsoleContext& context) {

    context.getIO().requestInputLine();
    std::string input = tokenizer_->read(context.getIO()).getData().value();
    if (input.empty()) {
        context.getIO().log("Task date must not be empty!");
        return std::make_shared<ParseTaskDate>();
    }
    using namespace boost::gregorian;
    try {
        context.getTaskBuffer().date_ = BoostDate(from_string(input));
    } catch (...) {
        context.getIO().log("Incorrect date!");
        return std::make_shared<ParseTaskDate>();
    }
    return std::make_shared<T_next>();
}

template<class T_next, class T_exit>
void ParseTaskDate<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskDate<
                    AddTaskState,
                    ParseCommand>;
template class ParseTaskDate<
                    AddSubTaskState,
                    ParseCommand>;
