//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEADDTYPE_H
#define TODOLIST_PARSEADDTYPE_H

class ConsoleContext;
class Tokenizer;
#include "State.h"

class ParseAddType : public State {

public:
    explicit ParseAddType(std::unique_ptr<Tokenizer>);

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &context, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;
};


#endif //TODOLIST_PARSEADDTYPE_H
