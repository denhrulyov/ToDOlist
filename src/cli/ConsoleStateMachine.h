//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_CONSOLESTATEMACHINE_H
#define TODOLIST_CONSOLESTATEMACHINE_H

#include "ConsoleContext.h"
#include "states/State.h"

class ConsoleStateMachine {

public:
    ConsoleStateMachine(std::unique_ptr<ConsoleContext> context,
                        const std::shared_ptr<State>& start_state);

public:
    void                                    run();


private:
    std::unique_ptr<ConsoleContext>         context_;
    std::shared_ptr<State>                  current_state_;
};


#endif //TODOLIST_CONSOLESTATEMACHINE_H
