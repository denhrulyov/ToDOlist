//
// Created by denis on 05.10.20.
//

#ifndef TODOLIST_SAVETOFILESTATE_H
#define TODOLIST_SAVETOFILESTATE_H


#include "State.h"

class SaveToFileState : public State {

public:
    void                            print(ConsoleContextInterface &context) override;
    std::shared_ptr<State>          execute(ConsoleContextInterface &context, StateFactoryInterface &) override;
    void                            help(ConsoleContextInterface &) override;


};

#endif //TODOLIST_SAVETOFILESTATE_H
