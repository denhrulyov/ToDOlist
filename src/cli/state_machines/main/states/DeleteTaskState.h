//
// Created by denis on 26.08.20.
//

#ifndef TODOLIST_DELETETASKSTATE_H
#define TODOLIST_DELETETASKSTATE_H

#include "State.h"

class DeleteTaskState : public State {

public:
    explicit
    DeleteTaskState();

public:
    void                            print(ConsoleContextInterface &) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;


};


#endif //TODOLIST_DELETETASKSTATE_H
