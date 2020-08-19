//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CONSOLE_H
#define TODOLIST_CONSOLE_H


#include "core/api/TODOList.h"

class State;



class Console {

public:
    explicit
    Console(std::unique_ptr<TaskServiceInterface>);

public:
    void run();
    void changeState(const std::shared_ptr<State>&);

private:
    std::unique_ptr<TaskServiceInterface>   service_;
    std::shared_ptr<State>                  state_;

};


#endif //TODOLIST_CONSOLE_H
