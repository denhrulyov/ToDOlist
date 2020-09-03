//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKPRIORITY_H
#define TODOLIST_PARSETASKPRIORITY_H


#include "ParseState.h"

class ParseTaskPriority : public ParseState {

public:
    explicit
    ParseTaskPriority();

public:

    void                    print(ConsoleContext&) override;
    ParseState::Event       execute(ConsoleContext&) override;
    void                    help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKPRIORITY_H
