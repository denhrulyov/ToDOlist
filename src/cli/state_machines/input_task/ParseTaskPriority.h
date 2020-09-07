//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKPRIORITY_H
#define TODOLIST_PARSETASKPRIORITY_H


#include <cli/state_machines/main/ConsoleContextInterface.h>
#include "ParseState.h"
#include "InputTaskContext.h"

class ParseTaskPriority : public ParseState {

public:
    explicit
    ParseTaskPriority();

public:

    void                    print(InputTaskContextInterface &) override;
    Event                   execute(InputTaskContextInterface &) override;
    void                    help(InputTaskContextInterface &) override;
};


#endif //TODOLIST_PARSETASKPRIORITY_H
