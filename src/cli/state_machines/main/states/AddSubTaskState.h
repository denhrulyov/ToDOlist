//
// Created by denis on 21.08.20.
//

#ifndef TODOLIST_ADDSUBTASKSTATE_H
#define TODOLIST_ADDSUBTASKSTATE_H

#include "State.h"
#include "cli/state_machines/main/ConsoleContext.h"
class Tokenizer;

class AddSubTaskState : public State {

public:
    explicit
    AddSubTaskState(std::unique_ptr<Tokenizer>);

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &context, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;
};


#endif //TODOLIST_ADDSUBTASKSTATE_H
