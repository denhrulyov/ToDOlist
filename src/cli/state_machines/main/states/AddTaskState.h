//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_ADDTASK_H
#define TODOLIST_ADDTASK_H

#include "State.h"

class Tokenizer;

class AddTaskState : public State {

public:
    explicit
    AddTaskState(std::unique_ptr<Tokenizer>);

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &context, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;
};


#endif //TODOLIST_ADDTASK_H
