//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSETASK_H
#define TODOLIST_PARSETASK_H

#include "ParseState.h"

class ParseTask : public ParseState {

public:
    explicit ParseTask();

public:
    virtual void        print(ConsoleContext& context) = 0;
    virtual std::shared_ptr<State>       execute(ConsoleContext&) = 0;

public:
    virtual ~ParseTask() = default;

};


#endif //TODOLIST_PARSETASK_H
