//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKLABEL_H
#define TODOLIST_PARSETASKLABEL_H

#include "ParseState.h"

class ParseTaskLabel : public ParseState {

public:
    explicit
    ParseTaskLabel();

public:
    void                        print(ConsoleContext& context) override;
    ParseState::Event           execute(ConsoleContext&) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKLABEL_H
