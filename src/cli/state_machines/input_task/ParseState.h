//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H


#include <cli/state_machines/main/ConsoleContextInterface.h>
#include "InputTaskContext.h"
#include "ParseStateFactoryInterface.h"

class ConsoleContext;

class ParseState {

public:
    enum class Event {
        SUCCESS,
        FAIL,
        EXIT
    };

public:
    explicit ParseState();

public:
    virtual void                         print(InputTaskContextInterface &) = 0;
    virtual Event                        execute(InputTaskContextInterface &) = 0;
    virtual void                         help(InputTaskContextInterface &) = 0;

    virtual ~ParseState() = default;
};


#endif //TODOLIST_PARSESTATE_H
