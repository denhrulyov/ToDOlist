//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESHOWPARAM_H
#define TODOLIST_PARSESHOWPARAM_H

#include "State.h"


class ParseShowParam : public State {

public:
    explicit ParseShowParam(std::unique_ptr<Tokenizer>);

public:
    void                     print(ConsoleContextInterface &)    override;
    std::shared_ptr<State>   execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                     help(ConsoleContextInterface &)     override;

private:
    std::unique_ptr<Tokenizer> tokenizer_;
};



#endif //TODOLIST_PARSESHOWPARAM_H
