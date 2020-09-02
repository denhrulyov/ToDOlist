//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKNAME_H
#define TODOLIST_PARSETASKNAME_H

#include "ParseState.h"

class ParseTaskName : public ParseState {

public:
    explicit
    ParseTaskName();

public:
    void                    print(ConsoleContext& context) override;
    ParseState::Event       execute(ConsoleContext&) override;
    void                    help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKNAME_H
