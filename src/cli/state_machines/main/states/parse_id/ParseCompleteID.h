//
// Created by denis on 14.09.20.
//

#ifndef TODOLIST_PARSECOMPLETEID_H
#define TODOLIST_PARSECOMPLETEID_H

#include "ParseID.h"

class ParseCompleteID : public ParseID {

public:
    std::shared_ptr<State> switchGood(ConsoleContextInterface &, StateFactoryInterface &) override;
};


#endif //TODOLIST_PARSECOMPLETEID_H
