//
// Created by denis on 25.08.20.
//

#ifndef TODOLIST_PARSECOMMAND_H
#define TODOLIST_PARSECOMMAND_H

#include "State.h"
class Tokenizer;

class ParseCommand : public State {

public:
    explicit
    ParseCommand(std::unique_ptr<Tokenizer>);

public:
    void                                print(ConsoleContext& context) override;
    std::shared_ptr<State>              execute(ConsoleContext &, StateFactoryInterface &) override;
    void                                help(ConsoleContext&) override;

private:
    std::unique_ptr<Tokenizer>          tokenizer_;
};


#endif //TODOLIST_PARSECOMMAND_H
