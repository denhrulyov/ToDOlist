//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_SHOWSTATE_H
#define TODOLIST_SHOWSTATE_H

#include "State.h"


class ShowState : public State {

public:
    explicit ShowState();

public:
    void                     print(ConsoleContext&)    override;
    std::shared_ptr<State>   execute(ConsoleContext &, StateFactoryInterface &) override;
    void                     help(ConsoleContext&)     override;

private:
    std::unique_ptr<Tokenizer> tokenizer_;
};



#endif //TODOLIST_SHOWSTATE_H
