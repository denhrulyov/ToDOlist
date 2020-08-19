//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H

#include "State.h"

class Console;

class ParseState : public State {

public:
    explicit
    ParseState(Console&);

public:
    virtual void                    print() = 0;
    virtual std::shared_ptr<State>  read() = 0;
};


#endif //TODOLIST_PARSESTATE_H
