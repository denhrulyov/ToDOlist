//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKPRIORITY_H
#define TODOLIST_PARSETASKPRIORITY_H


#include "ParseState.h"
#include "InputTaskContext.h"

class ParseTaskPriority : public ParseState {

public:
    explicit
    ParseTaskPriority();

public:

    void                    print(InputTaskContext &) override;
    ParseState::Event       execute(InputTaskContext &) override;
    void                    help(InputTaskContext &) override;
};


#endif //TODOLIST_PARSETASKPRIORITY_H
