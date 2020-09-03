//
// Created by denis on 26.08.20.
//

#ifndef TODOLIST_DELETETASKSTATE_H
#define TODOLIST_DELETETASKSTATE_H

#include "State.h"

class DeleteTaskState : public State {

public:
    explicit
    DeleteTaskState();

public:
    void                            print(ConsoleContext&) override;
    std::shared_ptr<State>          execute(ConsoleContext&) override;
    void                            help(ConsoleContext&) override;


};


#endif //TODOLIST_DELETETASKSTATE_H
