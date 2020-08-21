//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_ADDTASK_H
#define TODOLIST_ADDTASK_H

#include "State.h"

class AddTaskState : public State {

public:
    explicit
    AddTaskState(const std::shared_ptr<State>&);

public:
    void                    print(ConsoleContext& context) override;
    std::shared_ptr<State>  execute(ConsoleContext& context) override;
};


#endif //TODOLIST_ADDTASK_H
