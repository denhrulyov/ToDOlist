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
            return ParseState::Event::FAIL;
    }
}
