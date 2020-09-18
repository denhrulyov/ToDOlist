//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H


#include <cli/state_machines/main/ConsoleContextInterface.h>
#include "cli/tokenization/SpecwordFinder.h"
#include "InputTaskContext.h"
#include "ParseStateFactoryInterface.h"

class ConsoleContext;

/*
 * class defining input state flow
 *
 * @author Denis Hrulov
 */
class ParseState {

public:
    enum class Event {
        SUCCESS,
        INCORRECT,
        ABORT,
        EXIT
    };

public:
    explicit ParseState();

public:
    /*
     *
     * prints information about current state
     *
     * @param context containing TodoList CLI data
     *
     */
    virtual void                         print(InputTaskContextInterface &) = 0;
    /*
    *
    * prints additional information about requested input format
    *
    * @param context containing task data
    *
    */
    virtual Event                        processInput(InputTaskContextInterface &) = 0;
    /*
     *
     * Analyzes system state with user input, operates with system and returns next state to switch
     *
     * @param context containing task data
     */
    virtual void                         help(InputTaskContextInterface &) = 0;

    virtual Event                        execute(InputTaskContextInterface &);
    virtual ~ParseState() = default;

public:
    virtual Event                       dispatchSpecWord(Keyword kw);
};


#endif //TODOLIST_PARSESTATE_H
