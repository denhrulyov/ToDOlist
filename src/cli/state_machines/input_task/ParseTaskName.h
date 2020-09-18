//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKNAME_H
#define TODOLIST_PARSETASKNAME_H

#include <cli/state_machines/main/ConsoleContextInterface.h>
#include "ParseState.h"
#include "InputTaskContext.h"

class ParseTaskName : public ParseState {

public:
    explicit
    ParseTaskName();

public:
    void                    print(InputTaskContextInterface &context) override;
    Event                   processInput(InputTaskContextInterface &) override;
    void                    help(InputTaskContextInterface &) override;
};


#endif //TODOLIST_PARSETASKNAME_H
