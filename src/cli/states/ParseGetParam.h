//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEGETPARAM_H
#define TODOLIST_PARSEGETPARAM_H

#include "ParseState.h"
class ConsoleContext;

class ParseGetParam : public ParseState {

public:
    explicit
    ParseGetParam(const std::shared_ptr<State>&);
};


#endif //TODOLIST_PARSEGETPARAM_H
