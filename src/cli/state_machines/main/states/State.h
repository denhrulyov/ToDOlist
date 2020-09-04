//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STATE_H
#define TODOLIST_STATE_H

#include <memory>
#include <iostream>
#include "cli/state_machines/main/ConsoleContextInterface.h"
#include "cli/state_machines/main/tokenization/Tokenizer.h"
#include "cli/state_machines/main/state_factory/StateFactoryInterface.h"
#include "cli/state_machines/main/state_factory/Visitor.h"



class State {

public:
    explicit
    State();

public:
    virtual void                     print(ConsoleContextInterface &)                            = 0;
    virtual void                     help(ConsoleContextInterface &)                             = 0;
    virtual std::shared_ptr<State>   execute(ConsoleContextInterface &, StateFactoryInterface &) = 0;


public:
    virtual                          ~State()                                   = default;

};





#endif //TODOLIST_STATE_H
