//
// Created by denis on 15.09.20.
//

#ifndef TODOLIST_SHOWSUBTASKSSTATE_H
#define TODOLIST_SHOWSUBTASKSSTATE_H


#include "State.h"

class ShowSubTasksState : public State {
public:
public:
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            print(ConsoleContextInterface &) override;
    void                            help(ConsoleContextInterface &) override;
};


#endif //TODOLIST_SHOWSUBTASKSSTATE_H
