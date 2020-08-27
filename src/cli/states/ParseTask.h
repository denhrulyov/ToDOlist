//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSETASK_H
#define TODOLIST_PARSETASK_H

#include "ParseState.h"

class ParseTask : public ParseState {

public:
    explicit ParseTask(const std::shared_ptr<State>& next_state);

public:
    virtual void        print(ConsoleContext& context) = 0;
    virtual void        execute(ConsoleContext&) = 0;

public:
    virtual ~ParseTask() = default;

};


#endif //TODOLIST_PARSETASK_H
