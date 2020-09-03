//
// Created by denis on 03.09.20.
//
#include "DeleteStateParseID.h"

#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/states/DeleteTaskState.h"
#include "cli/state_machines/main/states/ParseCommand.h"
#include "cli/state_machines/main/states/AddTaskState.h"
#include "cli/state_machines/main/states/InputState.h"
#include "cli/state_machines/main/states/DeleteTaskState.h"
#include "cli/state_machines/main/TaskTableIO.h"



std::shared_ptr<State> DeleteStateParseID::switchGood(ConsoleContext &) {
    return std::make_shared<DeleteTaskState>();
}
