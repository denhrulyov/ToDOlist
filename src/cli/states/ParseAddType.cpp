//
// Created by denis on 18.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseTaskName.h"
#include "ParseAddType.h"
#include "State.h"
#include "StartState.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "ParseTaskDate.h"
#include "ParseTaskLabel.h"
#include "ParseTaskPriority.h"
#include "ParseCommand.h"
#include "ParseID.h"
#include "Utils.h"



ParseAddType::ParseAddType(const std::shared_ptr<State>& next_state)
:
ParseState(next_state)
{}

void ParseAddType::print(ConsoleContext& context) {

}

void ParseAddType::execute(ConsoleContext& context) {
    if (context.getIO().isEmpty()) {
        context.getIO().log("Specify what to add!");
        help(context);
        next_state_ = std::make_shared<ParseCommand>(nullptr);
        return;
    }
    std::string input = context.getIO().read();
    if (input == "task") {
        next_state_ =
                create_chain<
                        ParseTaskName<StartState, StartState>,
                        ParseTaskPriority<StartState, StartState>,
                        ParseTaskLabel<StartState, StartState>,
                        ParseTaskDate<StartState, StartState>,
                        AddTaskState>();
    } else if (input == "subtask") {
        next_state_ =
                create_chain<
                        ParseID,
                        ParseTaskName<StartState, StartState>,
                        ParseTaskPriority<StartState, StartState>,
                        ParseTaskLabel<StartState, StartState>,
                        ParseTaskDate<StartState, StartState>,
                        AddSubTaskState>();
    } else {
        context.getIO().log("Invalid add parameter!");
        help(context);
        next_state_ = std::make_shared<ParseCommand>(nullptr);
    }
}

void ParseAddType::help(ConsoleContext &context) {
    context.getIO().log("Available parameters:");
    context.getIO().log("-  task");
    context.getIO().log("-  subtask");
}
