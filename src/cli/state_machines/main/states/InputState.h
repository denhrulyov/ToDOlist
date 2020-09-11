//
// Created by denis on 01.09.20.
//

#ifndef TODOLIST_INPUTSTATE_H
#define TODOLIST_INPUTSTATE_H

#include "State.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include "cli/state_machines/main/ConsoleContext.h"

template<class T_next, class T_exit>
class InputState : public State {

public:
    explicit InputState(std::unique_ptr<InputTaskStateMachine>);

public:
    std::shared_ptr<State>          execute(ConsoleContextInterface &, StateFactoryInterface &factory) override;
    void                            print(ConsoleContextInterface &) override;
    void                            help(ConsoleContextInterface &) override;


private:
    std::unique_ptr<InputTaskStateMachine> machine_;
};

template<class T_next, class T_exit>
std::shared_ptr<State> InputState<T_next, T_exit>::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().clear();
    switch (machine_->run()) {
        case InputTaskStateMachine::Result::SUCCESS:
            context.fillTaskBuffer(machine_->extractTask());
            return factory.getInstance(Of<T_next>());
        case InputTaskStateMachine::Result::FAIL:
            return factory.getInstance(Of<T_exit>());
        default:
            return nullptr;
    }
}

template<class T_next, class T_exit>
void InputState<T_next, T_exit>::print(ConsoleContextInterface &) {

}

template<class T_next, class T_exit>
void InputState<T_next, T_exit>::help(ConsoleContextInterface &) {

}

template<class T_next, class T_exit>
InputState<T_next, T_exit>::InputState(std::unique_ptr<InputTaskStateMachine> machine)
:
machine_(std::move(machine))
{}



#endif //TODOLIST_INPUTSTATE_H
