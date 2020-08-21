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
#include "ParseID.h"
#include "Utils.h"

ParseAddType::ParseAddType(const std::shared_ptr<State>& next_state)
:
ParseState(next_state)
{}

void ParseAddType::print(ConsoleContext& context) {
    context.getIO().log("Specify what to add");
}

std::shared_ptr<State> ParseAddType::execute(ConsoleContext& context) {
    std::string input = context.getIO().read();
    if (input == "task") {
        auto next_state =
                create_chain<
                        ParseTaskName,
                        ParseTaskPriority,
                        ParseTaskLabel,
                        ParseTaskDate,
                        AddTaskState>();
        return next_state;
    } else if (input == "subtask") {
        auto next_state =
                create_chain<
                        ParseID,
                        ParseTaskName,
                        ParseTaskPriority,
                        ParseTaskLabel,
                        ParseTaskDate,
                        AddSubTaskState>();
        return next_state;
    } else {
        context.getIO().log("Invalid add argument!");
        return std::make_shared<StartState>(nullptr);
    }
}
