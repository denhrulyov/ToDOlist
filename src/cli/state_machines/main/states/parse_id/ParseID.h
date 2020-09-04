//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "cli/state_machines/main/states/State.h"

class ParseID : public State {

public:
    explicit
    ParseID();

public:
    void                        print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>      execute(ConsoleContextInterface &context, StateFactoryInterface &factory) override;
    void                        help(ConsoleContextInterface &) override;

public:
    virtual std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) = 0;
};


#endif //TODOLIST_PARSEID_H
