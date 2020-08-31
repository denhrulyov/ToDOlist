//
// Created by denis on 20.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"

template<class T_next, class T_exit>
ParseTaskLabel<T_next, T_exit>::ParseTaskLabel()
: ParseTask()
{}

template<class T_next, class T_exit>
void ParseTaskLabel<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Label:");
}

template<class T_next, class T_exit>
std::shared_ptr<State> ParseTaskLabel<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task label must not be empty!");
        return std::make_shared<ParseTaskLabel>();
    }
    context.getTaskBuffer().label_ = input;
    return std::make_shared<T_next>();
}

template<class T_next, class T_exit>
void ParseTaskLabel<T_next, T_exit>::help(ConsoleContext &) {

}

template class ParseTaskLabel<
                    ParseTaskDate<
                            AddTaskState,
                            ParseCommand>,
                    ParseCommand>;

template class ParseTaskLabel<
                    ParseTaskDate<
                            AddSubTaskState,
                            ParseCommand>,
                    ParseCommand>;