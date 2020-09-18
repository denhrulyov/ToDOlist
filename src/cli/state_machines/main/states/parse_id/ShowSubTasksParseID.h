//
// Created by denis on 15.09.20.
//

#ifndef TODOLIST_SHOWSUBTASKSPARSEID_H
#define TODOLIST_SHOWSUBTASKSPARSEID_H

#include "ParseID.h"

class ShowSubTasksParseID : public ParseID {

public:
    std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) override;
};


#endif //TODOLIST_SHOWSUBTASKSPARSEID_H
