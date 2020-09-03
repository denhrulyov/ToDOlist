//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CLI_H
#define TODOLIST_CLI_H

#include "cli/state_machines/main/ConsoleStateMachine.h"
#include "cli/state_machines/main/states/StartState.h"
#include "core/api/TODOList.h"

namespace todo_list_cli {

    ConsoleStateMachine createCLI() {
        auto context = std::make_unique<ConsoleContext>(std::move(todo_list::createService()));
        auto& ref_context = *context;
        ConsoleStateMachine cli(
                std::move(context), std::make_shared<StartState>()
                );
        return cli;
    }
}


#endif //TODOLIST_CLI_H
