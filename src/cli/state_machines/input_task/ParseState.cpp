//
// Created by denis on 18.08.20.
//

#include "ParseState.h"

ParseState::ParseState()
{}

ParseState::Event ParseState::dispatchSpecWord(Keyword kw) {
    switch (kw) {
        case Keyword::ABORT:
            return ParseState::Event::ABORT;
        case Keyword::EXIT:
            return ParseState::Event::EXIT;
        default:
            return ParseState::Event::INCORRECT;
    }
}

ParseState::Event ParseState::execute(InputTaskContextInterface &context) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd);
    }
    return processInput(context);
}
