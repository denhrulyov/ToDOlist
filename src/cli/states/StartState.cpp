//
// Created by denis on 18.08.20.
//

#include "StartState.h"
#include "ParseAddType.h"
#include "cli/Console.h"

StartState::StartState(Console & console)
:
State(console)
{}


std::shared_ptr<State>
StartState::read() {
    std::string command;
    std::cin >> command;
    if (command == "add") {
        console_.changeState(std::make_shared<ParseAddType>(console_));
    } else {
        console_.changeState(std::make_shared<StartState>(console_));
    }
    return nullptr;
}

void
StartState::print() {
    std::cout << "Welcome to TODO list CLI. Input command to execute" << std::endl;
}

