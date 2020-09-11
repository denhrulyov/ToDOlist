//
// Created by denis on 11.09.20.
//

#ifndef TODOLIST_INPUTTASKSTATE_H
#define TODOLIST_INPUTTASKSTATE_H

#include "InputState.h"

class InputTaskState : public InputState {

public:
    explicit InputTaskState(std::unique_ptr<InputTaskStateMachine>);

public:
    std::shared_ptr<State> getNextState(StateFactoryInterface &factory) override;
    std::shared_ptr<State> getExitState(StateFactoryInterface &factory) override;
};


#endif //TODOLIST_INPUTTASKSTATE_H
