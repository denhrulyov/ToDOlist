//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_DELETESTATEPARSEID_H
#define TODOLIST_DELETESTATEPARSEID_H

#include "ParseID.h"

class DeleteStateParseID : public ParseID {

public:
    std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) override;
};


#endif //TODOLIST_DELETESTATEPARSEID_H
