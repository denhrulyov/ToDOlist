//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_SHOWSTATE_H
#define TODOLIST_SHOWSTATE_H

#include "State.h"


class ShowState : public State {

public:
    explicit ShowState(std::unique_ptr<Tokenizer>);

public:
    void                     print(ConsoleContextInterface &)    override;
    std::shared_ptr<State>   execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                     help(ConsoleContextInterface &)     override;

private:
    std::unique_ptr<Tokenizer> tokenizer_;
};



#endif //TODOLIST_SHOWSTATE_H
