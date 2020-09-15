//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STATE_H
#define TODOLIST_STATE_H

#include <memory>
#include <iostream>
#include "cli/state_machines/main/ConsoleContextInterface.h"
#include "cli/tokenization/Tokenizer.h"
#include "cli/tokenization/SpecwordFinder.h"
#include "cli/state_machines/main/state_factory/StateFactoryInterface.h"

/*
 * class defining system behavior according to user input and system state
 *
 * @author Denis Hrulov
 */
class State {

public:
    explicit
    State();

public:
    /*
     *
     * prints information about current state
     *
     * @param context containing TodoList CLI data
     *
     */
    virtual void                     print(ConsoleContextInterface &)                            = 0;
    /*
     *
     * prints additional information about requested input format
     *
     * @param context containing TodoList CLI data
     *
     */
    virtual void                     help(ConsoleContextInterface &)                             = 0;
    /*
     *
     * Analyzes system state with user input, operates with system and returns next state to switch
     *
     * @param context containing TodoList CLI data
     * @param object responsible for creating states
     */
    virtual std::shared_ptr<State>   execute(ConsoleContextInterface &, StateFactoryInterface &) = 0;

public:
    virtual std::shared_ptr<State>   dispatchSpecWord(Keyword kw, StateFactoryInterface&);


public:
    virtual                          ~State()                                   = default;


};





#endif //TODOLIST_STATE_H
