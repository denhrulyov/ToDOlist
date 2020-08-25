//
// Created by denis on 21.08.20.
//

#ifndef TODOLIST_ADDSUBTASKSTATE_H
#define TODOLIST_ADDSUBTASKSTATE_H

#include "State.h"
#include "cli/ConsoleContext.h"

class AddSubTaskState : public State {

public:
    explicit
    AddSubTaskState(const std::shared_ptr<State>&);

public:
    void                print(ConsoleContext& context) override;
    void                execute(ConsoleContext& context) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_ADDSUBTASKSTATE_H
