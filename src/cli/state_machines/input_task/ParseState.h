//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H


#include "InputTaskContext.h"

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
    virtual void                         print(InputTaskContext &) = 0;
    virtual Event                        execute(InputTaskContext &) = 0;
    virtual void                         help(InputTaskContext &) = 0;

    virtual ~ParseState() = default;
};


#endif //TODOLIST_PARSESTATE_H
