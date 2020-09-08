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

class ParseState {

public:
    enum class Event {
        SUCCESS,
        FAIL,
        ABORT,
        EXIT
    };

public:
    explicit ParseState();

public:
    virtual void                         print(InputTaskContextInterface &) = 0;
    virtual Event                        execute(InputTaskContextInterface &) = 0;
    virtual void                         help(InputTaskContextInterface &) = 0;

    virtual ~ParseState() = default;

public:
    virtual Event                       dispatchSpecWord(Keyword kw);
};


#endif //TODOLIST_PARSESTATE_H
