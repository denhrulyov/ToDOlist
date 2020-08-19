//
// Created by denis on 18.08.20.
//

#include "Console.h"
#include "states/State.h"

Console::Console(
        std::unique_ptr<TaskServiceInterface> service)
        :
        service_(std::move(service))
{}

void Console::changeState(const std::shared_ptr<State>& next_state) {
    state_ = next_state;
}

void Console::run() {
    state_->read();
}





