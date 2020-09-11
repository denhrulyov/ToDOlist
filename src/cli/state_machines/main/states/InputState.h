//
// Created by denis on 01.09.20.
//

#ifndef TODOLIST_INPUTSTATE_H
#define TODOLIST_INPUTSTATE_H

#include "State.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include "cli/state_machines/main/ConsoleContext.h"

class InputState : public State {

public:
    explicit InputState(std::unique_ptr<InputTaskStateMachine>);

public:
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &factory) override;
    void                            print(ConsoleContextInterface &) override;
    void                            help(ConsoleContextInterface &) override;

public:
    virtual std::shared_ptr<State>          getNextState(StateFactoryInterface &factory) = 0;
    virtual std::shared_ptr<State>          getExitState(StateFactoryInterface &factory) = 0;

private:
    std::unique_ptr<InputTaskStateMachine> machine_;
};





#endif //TODOLIST_INPUTSTATE_H
