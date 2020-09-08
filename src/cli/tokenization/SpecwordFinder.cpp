//
// Created by denis on 08.09.20.
//

#include "SpecwordFinder.h"

Keyword SpecwordFinder::findSpecWord(const std::string_view &input)  {
    if (input.find("__exit__") != std::string::npos) {
        return Keyword::EXIT;
    } else if (input.find("__abort__") != std::string::npos) {
        return Keyword::ABORT;
    } else {
        return Keyword::NONE;
    }
}


