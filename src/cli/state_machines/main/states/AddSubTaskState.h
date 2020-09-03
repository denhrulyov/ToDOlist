//
// Created by denis on 21.08.20.
//

#ifndef TODOLIST_ADDSUBTASKSTATE_H
#define TODOLIST_ADDSUBTASKSTATE_H

#include "State.h"
#include "cli/state_machines/main/ConsoleContext.h"

class AddSubTaskState : public State {

public:
    explicit
    AddSubTaskState();

public:
    void                            print(ConsoleContext& context) override;
    std::shared_ptr<State>          execute(ConsoleContext& context) override;
    void                            help(ConsoleContext&) override;
};


#endif //TODOLIST_ADDSUBTASKSTATE_H
