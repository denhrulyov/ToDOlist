//
// Created by denis on 25.08.20.
//

#ifndef TODOLIST_PARSECOMMAND_H
#define TODOLIST_PARSECOMMAND_H

#include "ParseState.h"

class ParseCommand : public ParseState {

public:
    explicit
    ParseCommand();

public:
    void                                print(ConsoleContext& context) override;
    std::shared_ptr<State>              execute(ConsoleContext&) override;
    void                                help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSECOMMAND_H
