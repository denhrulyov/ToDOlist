//
// Created by denis on 15.09.20.
//

#ifndef TODOLIST_PARSEPOSTPONEID_H
#define TODOLIST_PARSEPOSTPONEID_H

#include "ParseID.h"

class ParsePostponeID : public ParseID {

public:
    std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) override;
};


#endif //TODOLIST_PARSEPOSTPONEID_H
