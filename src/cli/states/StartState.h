//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STARTSTATE_H
#define TODOLIST_STARTSTATE_H

#include "State.h"
#include "ParseState.h"

class StartState : public State {

public:
    explicit
    StartState(Console&);

public:
    std::shared_ptr<State>          read() override;
    void                            print() override;

};


#endif //TODOLIST_STARTSTATE_H
