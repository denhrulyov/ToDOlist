//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "cli/state_machines/main/states/State.h"

class ParseID : public State {

public:
    explicit
    ParseID();

public:
    void                        print(ConsoleContext& context) override;
    std::shared_ptr<State>      execute(ConsoleContext& context) override;
    void                        help(ConsoleContext&) override;

public:
    virtual std::shared_ptr<State> switchGood(ConsoleContext &) = 0;
};


#endif //TODOLIST_PARSEID_H
