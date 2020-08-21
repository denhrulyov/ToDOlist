//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STATE_H
#define TODOLIST_STATE_H

#include <memory>
#include <iostream>

class ConsoleContext;



class State {

public:
    State(const std::shared_ptr<State>& next_state) : next_state_(next_state) {};

public:
    virtual void                     print(ConsoleContext&)                             = 0;
    virtual std::shared_ptr<State>   execute(ConsoleContext&)                           = 0;

public:
    virtual                          ~State()                                   = default;

protected:
    std::shared_ptr<State> next_state_;

};





#endif //TODOLIST_STATE_H
