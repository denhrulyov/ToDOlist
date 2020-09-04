//
// Created by denis on 25.08.20.
//

#ifndef TODOLIST_PARSESHOWTAG_H
#define TODOLIST_PARSESHOWTAG_H

#include "State.h"

class ParseShowTag : public State {

public:
    explicit
    ParseShowTag();

public:
    void                            print(ConsoleContext& context) override;
    std::shared_ptr<State>          execute(ConsoleContext &, StateFactoryInterface &) override;
    void                            help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSESHOWTAG_H
