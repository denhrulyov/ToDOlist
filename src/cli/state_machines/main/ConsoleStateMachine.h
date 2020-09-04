//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_CONSOLESTATEMACHINE_H
#define TODOLIST_CONSOLESTATEMACHINE_H

#include "ConsoleContextInterface.h"
#include "cli/state_machines/main/states/State.h"

class ConsoleStateMachine {

public:
    ConsoleStateMachine(std::unique_ptr<ConsoleContextInterface> context,
                        std::unique_ptr<StateFactoryInterface> factory,
                        const std::shared_ptr<State>& start_state);

public:
    void                                    run();


private:
    std::unique_ptr<StateFactoryInterface>      factory_;
    std::unique_ptr<ConsoleContextInterface>    context_;
    std::shared_ptr<State>                      current_state_;
};


#endif //TODOLIST_CONSOLESTATEMACHINE_H
