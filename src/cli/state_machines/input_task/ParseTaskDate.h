//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKDATE_H
#define TODOLIST_PARSETASKDATE_H

#include "ParseState.h"
#include "InputTaskContext.h"


class ParseTaskDate : public ParseState {

public:
    explicit
    ParseTaskDate();

public:
    void                        print(InputTaskContext &context) override;
    ParseState::Event           execute(InputTaskContext &) override;
    void                        help(InputTaskContext &) override;
};


#endif //TODOLIST_PARSETASKDATE_H
