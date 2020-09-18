//
// Created by denis on 14.09.20.
//'[[[[[[[['/

#ifndef TODOLIST_POSTPONESTATE_H
#define TODOLIST_POSTPONESTATE_H

#include "State.h"

class PostponeState : public State {

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;
};


#endif //TODOLIST_POSTPONESTATE_H
