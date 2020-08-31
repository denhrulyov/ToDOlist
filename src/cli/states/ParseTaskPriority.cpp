//
// Created by denis on 19.08.20.
//

#include "ParseCommand.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "StartState.h"
#include "cli/ConsoleContext.h"
#include "ParseTaskDate.h"

template<class T_next, class T_exit>
ParseTaskPriority<T_next, T_exit>::ParseTaskPriority() :
        ParseTask()
{}

template<class T_next, class T_exit>
void ParseTaskPriority<T_next, T_exit>::print(ConsoleContext& context) {
    context.getIO().log("Task priority:");
}

template<class T_next, class T_exit>
std::shared_ptr<State> ParseTaskPriority<T_next, T_exit>::execute(ConsoleContext& context) {
    std::string input = context.getIO().readLine();
    if (input.empty()) {
        context.getIO().log("Task priority must not be empty");
        return std::make_shared<ParseTaskPriority>();
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
               return std::make_shared<ParseTaskPriority>();
    }
    return std::make_shared<T_next>();
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
                                                    ParseCommand>,
                                            ParseCommand>,
                                    ParseCommand>;

template class ParseTaskPriority<   ParseTaskLabel<
                                        ParseTaskDate<
                                                AddSubTaskState,
                                                ParseCommand>,
                                        ParseCommand>,
                                    ParseCommand>;