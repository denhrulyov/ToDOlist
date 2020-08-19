//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CLI_H
#define TODOLIST_CLI_H

#include "Console.h"
#include "states/StartState.h"

namespace todo_list_cli {

    Console createCLI() {
        auto cli = Console(todo_list::createService());
        cli.changeState(std::make_shared<StartState>(cli));
        return cli;
    }
}

#endif //TODOLIST_CLI_H
