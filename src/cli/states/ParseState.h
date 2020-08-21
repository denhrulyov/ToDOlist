//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H

#include "State.h"

class ConsoleContext;

class ParseState : public State {

public:
    explicit
    ParseState(const std::shared_ptr<State>&);

public:
    virtual void                    print(ConsoleContext&) = 0;
    virtual std::shared_ptr<State>  execute(ConsoleContext&) = 0;
};


#endif //TODOLIST_PARSESTATE_H
