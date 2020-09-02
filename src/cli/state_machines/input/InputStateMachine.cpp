//
// Created by denis on 01.09.20.
//

#include "InputStateMachine.h"
#include "ParseState.h"
#include "cli/ConsoleContext.h"

InputStateMachine::InputStateMachine(const std::vector<std::shared_ptr<ParseState>> &state_sequence, ConsoleContext& context)
:
state_sequence_(state_sequence),
context_(context)
{}

InputStateMachine::Result InputStateMachine::run() {

    for (const auto& state : state_sequence_) {
        ParseState::Event event;
        do {
            state->print(context_);
            event = state->execute(context_);
            if (event == ParseState::Event::EXIT) {
                return Result::FAIL;
            }
        } while(event != ParseState::Event::SUCCESS);
    }
    return Result::SUCCESS;
}
