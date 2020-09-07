//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_PARSESTATEFACTORYINTERFACE_H
#define TODOLIST_PARSESTATEFACTORYINTERFACE_H

#include <memory>
class ParseState;

class ParseStateFactoryInterface {

public:
    virtual std::shared_ptr<ParseState> getNextState() = 0;
    virtual ~ParseStateFactoryInterface() = default;
};


#endif //TODOLIST_PARSESTATEFACTORYINTERFACE_H
