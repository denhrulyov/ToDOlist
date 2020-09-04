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
    void                            print(ConsoleContext& context) override;
    std::shared_ptr<State>          execute(ConsoleContext &context, StateFactoryInterface &) override;
    void                            help(ConsoleContext&) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;
};


#endif //TODOLIST_ADDTASK_H
