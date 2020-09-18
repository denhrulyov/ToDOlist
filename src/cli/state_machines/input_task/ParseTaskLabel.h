//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKLABEL_H
#define TODOLIST_PARSETASKLABEL_H

#include "ParseState.h"
#include "InputTaskContext.h"

class ParseTaskLabel : public ParseState {

public:
    explicit
    ParseTaskLabel();

public:
    void                        print(InputTaskContextInterface &context) override;
    Event                       processInput(InputTaskContextInterface &) override;
    void                        help(InputTaskContextInterface &) override;
};


#endif //TODOLIST_PARSETASKLABEL_H
