//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_PARSESTATEFACTORY_H
#define TODOLIST_PARSESTATEFACTORY_H

#include "ParseStateFactoryInterface.h"
#include "cli/state_machines/utils/InitializerInterface.h"

class ParseStateFactory : public ParseStateFactoryInterface {

public:
    explicit ParseStateFactory();

public:
    std::shared_ptr<ParseState> getNextState() override ;
    std::shared_ptr<ParseState> getFirstState() override;


private:
    using ParseStateInitializer =       InitializerInterface<ParseState>;
    using InitializersArray =           std::array<std::unique_ptr<ParseStateInitializer>, 4>;

private:
    InitializersArray                   states_;
    InitializersArray::iterator         current_state_;
};


#endif //TODOLIST_PARSESTATEFACTORY_H
