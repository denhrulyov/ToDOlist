//
// Created by denis on 11.09.20.
//

#ifndef TODOLIST_INPUTSUBTASKSTATE_H
#define TODOLIST_INPUTSUBTASKSTATE_H

#include "InputState.h"

class InputSubTaskState : public InputState {

public:
    explicit InputSubTaskState(std::unique_ptr<InputTaskStateMachine>);

public:
    std::shared_ptr<State> getNextState(StateFactoryInterface &factory) override;
    std::shared_ptr<State> getExitState(StateFactoryInterface &factory) override;
};


#endif //TODOLIST_INPUTSUBTASKSTATE_H
