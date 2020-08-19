//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEGETPAREM_H
#define TODOLIST_PARSEGETPAREM_H

#include "ParseState.h"
class Console;

class ParseGetParam : public ParseState {

public:
    explicit
    ParseGetParam(Console&);
};


#endif //TODOLIST_PARSEGETPAREM_H
