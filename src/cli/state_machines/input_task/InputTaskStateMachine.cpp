//
// Created by denis on 01.09.20.
//

#include "InputTaskStateMachine.h"
#include "ParseState.h"
#include "cli/ConsoleContext.h"

InputTaskStateMachine::InputTaskStateMachine(const std::vector<std::shared_ptr<ParseState>> &state_sequence, ConsoleContext& context)
:
state_sequence_(state_sequence),
context_(context)
{}

typename InputTaskStateMachine::Result InputTaskStateMachine::run() {

    for (auto state : state_sequence_) {
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
