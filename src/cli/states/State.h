//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_STATE_H
#define TODOLIST_STATE_H

#include <memory>
#include <iostream>

class ConsoleContext;
class Tokenizer;


class State {

public:
    explicit
    State();

public:
    virtual void                     print(ConsoleContext&)                             = 0;
    virtual void                     help(ConsoleContext&)                              = 0;
    virtual std::shared_ptr<State>   execute(ConsoleContext&)                           = 0;
    virtual std::shared_ptr<State>   switchState(ConsoleContext&);


public:
    virtual                          ~State()                                   = default;

};





#endif //TODOLIST_STATE_H
