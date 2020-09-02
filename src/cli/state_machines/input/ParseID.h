//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "ParseState.h"

class ParseID : public ParseState {

public:
    explicit
    ParseID();

public:
    void                        print(ConsoleContext& context) override;
    ParseState::Event           execute(ConsoleContext& context) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSEID_H
