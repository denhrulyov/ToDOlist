//
// Created by denis on 26.08.20.
//

#ifndef TODOLIST_DELETETASKSTATE_H
#define TODOLIST_DELETETASKSTATE_H

#include "State.h"
#include "cli/tokenization/Tokenizer.h"

class DeleteTaskState : public State {

public:
    explicit
    DeleteTaskState(std::unique_ptr<Tokenizer>);

public:
    void                            print(ConsoleContextInterface &) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;

};


#endif //TODOLIST_DELETETASKSTATE_H
