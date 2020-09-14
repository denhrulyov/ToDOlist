//
// Created by denis on 14.09.20.
//

#ifndef TODOLIST_COMPLETESTATE_H
#define TODOLIST_COMPLETESTATE_H

#include "State.h"

class CompleteState : public State {

public:
    void                            print(ConsoleContextInterface &) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;
};


#endif //TODOLIST_COMPLETESTATE_H
