//
// Created by denis on 19.08.20.
//

#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "StartState.h"
#include "cli/ConsoleContext.h"
#include "ParseTaskDate.h"

template<class T_next, class T_exit>
ParseTaskPriority<T_next, T_exit>::ParseTaskPriority(const std::shared_ptr<State>& next_state) :
        ParseTask(next_state)
{}

template<class T_next, class T_exit>
void ParseTaskPriority<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Task priority:");
}

template<class T_next, class T_exit>
void ParseTaskPriority<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task priority must not be empty");
        next_state_ = std::make_shared<ParseTaskPriority>(next_state_);
        return;
    }
    for (auto &symbol : input) {
        symbol = std::tolower(symbol);
    }
           if (input == "first" || input == "1") {
               context.getTaskBuffer().priority_ = TaskPriority::FIRST;
    } else if (input == "second" || input == "2") {
               context.getTaskBuffer().priority_ = TaskPriority::SECOND;
    } else if (input == "third" || input == "3") {
               context.getTaskBuffer().priority_ = TaskPriority::THIRD;
    } else if (input == "none" || input == "0") {
               context.getTaskBuffer().priority_ = TaskPriority::NONE;
    } else {
               help(context);
               next_state_ = std::make_shared<ParseTaskPriority>(next_state_);
    }

}

template<class T_next, class T_exit>
void ParseTaskPriority<T_next, T_exit>::help(ConsoleContext& context) {
    context.getIO().log("Incorrect priority!");
    context.getIO().log("Possible : ");
    context.getIO().log("first    (1)");
    context.getIO().log("second   (2)");
    context.getIO().log("third    (3)");
    context.getIO().log("none     (0)");
}


template class ParseTaskPriority<   ParseTaskLabel<
                                            ParseTaskDate<
                                                    AddTaskState,
                                                    StartState>,
                                            StartState>,
                                    StartState>;

template class ParseTaskPriority<   ParseTaskLabel<
                                        ParseTaskDate<
                                                AddSubTaskState,
                                                StartState>,
                                        StartState>,
                                    StartState>;