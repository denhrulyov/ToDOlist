//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKDATE_H
#define TODOLIST_PARSETASKDATE_H

#include "ParseState.h"


class ParseTaskDate : public ParseState {

public:
    explicit
    ParseTaskDate();

public:
    void                        print(ConsoleContext& context) override;
    ParseState::Event           execute(ConsoleContext&) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKDATE_H
