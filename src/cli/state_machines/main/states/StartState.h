//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STARTSTATE_H
#define TODOLIST_STARTSTATE_H

#include "State.h"
class StartState : public State {

public:
    explicit
    StartState();

public:
    std::shared_ptr<State> execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            print(ConsoleContextInterface &) override;
    void                            help(ConsoleContextInterface &) override;

};


#endif //TODOLIST_STARTSTATE_H
