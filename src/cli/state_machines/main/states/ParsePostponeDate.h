//
// Created by denis on 15.09.20.
//

#ifndef TODOLIST_PARSEPOSTPONEDATE_H
#define TODOLIST_PARSEPOSTPONEDATE_H

#include "State.h"

class ParsePostponeDate : public State {

public:
    void                                print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>              execute(ConsoleContextInterface &, StateFactoryInterface &) override;
    void                                help(ConsoleContextInterface &) override;
};


#endif //TODOLIST_PARSEPOSTPONEDATE_H
