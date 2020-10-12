//
// Created by denis on 05.10.20.
//

#ifndef TODOLIST_LOADFROMFILESTATE_H
#define TODOLIST_LOADFROMFILESTATE_H


#include "State.h"

class LoadFromFileState : public State {

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &context, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;

};



#endif //TODOLIST_LOADFROMFILESTATE_H
