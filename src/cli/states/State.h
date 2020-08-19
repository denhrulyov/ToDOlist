//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STATE_H
#define TODOLIST_STATE_H

#include <memory>
#include <iostream>

class Console;

class State {

public:
    State(Console& console) : console_(console) {};

public:
    virtual void                     print()                         = 0;
    virtual std::shared_ptr<State>   read()             = 0;

public:
    virtual                          ~State()           = default;

protected:
    Console& console_;
};



#endif //TODOLIST_STATE_H
