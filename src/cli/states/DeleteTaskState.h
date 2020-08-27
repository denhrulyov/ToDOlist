//
// Created by denis on 26.08.20.
//

#ifndef TODOLIST_DELETETASKSTATE_H
#define TODOLIST_DELETETASKSTATE_H

#include "State.h"

class DeleteTaskState : public State {

public:
    explicit
    DeleteTaskState(const std::shared_ptr<State>&);

public:
    void                print(ConsoleContext&) override;
    void                execute(ConsoleContext&) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_DELETETASKSTATE_H
