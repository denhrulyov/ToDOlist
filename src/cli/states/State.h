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
    explicit
    State(const std::shared_ptr<State>& next_state);

public:
    virtual void                     print(ConsoleContext&)                             = 0;
    virtual void                     help(ConsoleContext&)                              = 0;
    virtual void                     execute(ConsoleContext&)                           = 0;
    virtual std::shared_ptr<State>   switchState(ConsoleContext&);


public:
    virtual                          ~State()                                   = default;

protected:
    std::shared_ptr<State> next_state_;

};





#endif //TODOLIST_STATE_H
