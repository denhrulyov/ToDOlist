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
    explicit ParseAddType();

public:
    void                            print(ConsoleContext& context) override;
    std::shared_ptr<State>          execute(ConsoleContext &context, StateFactoryInterface &) override;
    void                            help(ConsoleContext&) override;

private:
    std::unique_ptr<Tokenizer>      tokenizer_;
};


#endif //TODOLIST_PARSEADDTYPE_H
