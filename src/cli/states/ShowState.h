//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_SHOWSTATE_H
#define TODOLIST_SHOWSTATE_H

#include "State.h"

class ShowState : public State {

public:
    explicit ShowState(const std::shared_ptr<State>& next_state);

public:
    void                     print(ConsoleContext&)    override;
    void                     execute(ConsoleContext&)  override;
    void                     help(ConsoleContext&)     override;
};



#endif //TODOLIST_SHOWSTATE_H
