//
// Created by denis on 25.08.20.
//

#include "State.h"
#include "cli/state_machines/main/ConsoleContext.h"

State::State()
 {}

std::shared_ptr<State> State::dispatchSpecWord(Keyword kw, StateFactoryInterface& factory) {
    switch (kw) {
        case Keyword::ABORT:
            return Visitor<ParseCommand>().visit(factory);
        default:
            return nullptr;
    }
}

