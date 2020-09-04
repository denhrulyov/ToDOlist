//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_INPUTTASKPARSEID_H
#define TODOLIST_INPUTTASKPARSEID_H

#include "ParseID.h"

class InputTaskParseID : public ParseID {

public:
    std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) override ;
};


#endif //TODOLIST_INPUTTASKPARSEID_H
