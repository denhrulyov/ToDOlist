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
#include "cli/states/utils/Utils.h"



ParseAddType::ParseAddType()
:
ParseState()
{}

void ParseAddType::print(ConsoleContext& context) {

}

std::shared_ptr<State> ParseAddType::execute(ConsoleContext& context) {
    if (context.getIO().isEmpty()) {
        context.getIO().log("Specify what to add!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
    std::string input = context.getIO().read();
    if (input == "task") {
        return std::make_shared<
                InputChain<
                        pack<ParseTaskName,
                             ParseTaskPriority,
                             ParseTaskLabel,
                             ParseTaskDate>,
                        AddTaskState,
                        ParseCommand
                >
         >();
    } else if (input == "subtask") {
        return std::make_shared<
                InputChain<
                        pack<ParseID,
                             ParseTaskName,
                             ParseTaskPriority,
                             ParseTaskLabel,
                             ParseTaskDate>,
                        AddSubTaskState,
                        ParseCommand
                >
        >();
    } else {
        context.getIO().log("Invalid add parameter!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
}

void ParseAddType::help(ConsoleContext &context) {
    context.getIO().log("Available parameters:");
    context.getIO().log("-  task");
    context.getIO().log("-  subtask");
}
