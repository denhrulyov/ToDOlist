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
    StartState(const std::shared_ptr<State>&);

public:
    void                            execute(ConsoleContext&) override;
    void                            print(ConsoleContext&) override;
    void                            help(ConsoleContext&) override;

};


#endif //TODOLIST_STARTSTATE_H
