//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKNAME_H
#define TODOLIST_PARSETASKNAME_H

#include "ParseState.h"
#include "InputTaskContext.h"

class ParseTaskName : public ParseState {

public:
    explicit
    ParseTaskName();

public:
    void                    print(InputTaskContext &context) override;
    ParseState::Event       execute(InputTaskContext &) override;
    void                    help(InputTaskContext &) override;
};


#endif //TODOLIST_PARSETASKNAME_H
