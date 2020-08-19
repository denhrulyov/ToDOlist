//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEADDTYPE_H
#define TODOLIST_PARSEADDTYPE_H

class Console;
#include "State.h"

class ParseAddType : public State {

public:
    explicit ParseAddType(Console&);

public:
    void                    print();
    std::shared_ptr<State>  read();
};


#endif //TODOLIST_PARSEADDTYPE_H
