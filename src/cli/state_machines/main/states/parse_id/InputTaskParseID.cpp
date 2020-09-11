//
// Created by denis on 03.09.20.
//

#include "InputTaskParseID.h"
#include "cli/state_machines/main/states/AddSubTaskState.h"
#include "cli/state_machines/main/states/InputState.h"
#include "cli/state_machines/main/states/ParseCommand.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"

std::shared_ptr<State> InputTaskParseID::switchGood(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    return factory.getInstanceOfSubTaskInputChain();
}
