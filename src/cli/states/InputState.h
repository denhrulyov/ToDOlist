//
// Created by denis on 01.09.20.
//

#ifndef TODOLIST_INPUTSTATE_H
#define TODOLIST_INPUTSTATE_H

#include "State.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include "cli/ConsoleContext.h"

template<class T_next, class T_exit>
class InputState : public State {

public:
    explicit InputState(std::unique_ptr<InputTaskStateMachine>);

public:
    std::shared_ptr<State>          execute(ConsoleContext&) override;
    void                            print(ConsoleContext&) override;
    void                            help(ConsoleContext&) override;


private:
    std::unique_ptr<InputTaskStateMachine> machine_;
};

template<class T_next, class T_exit>
std::shared_ptr<State> InputState<T_next, T_exit>::execute(ConsoleContext & context) {
    context.getIO().clear();
    switch (machine_->run()) {
        case InputTaskStateMachine::Result::SUCCESS:
            return std::make_shared<T_next>();
        case InputTaskStateMachine::Result::FAIL:
            return std::make_shared<T_exit>();
        default:
            return nullptr;
    }
}

template<class T_next, class T_exit>
void InputState<T_next, T_exit>::print(ConsoleContext &) {

}

template<class T_next, class T_exit>
void InputState<T_next, T_exit>::help(ConsoleContext &) {

}

template<class T_next, class T_exit>
InputState<T_next, T_exit>::InputState(std::unique_ptr<InputTaskStateMachine> machine)
:
machine_(std::move(machine))
{}



#endif //TODOLIST_INPUTSTATE_H
