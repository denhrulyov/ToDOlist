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
    std::shared_ptr<State> execute(ConsoleContext &, StateFactoryInterface &) override;
    void                            print(ConsoleContext&) override;
    void                            help(ConsoleContext&) override;

};


#endif //TODOLIST_STARTSTATE_H
