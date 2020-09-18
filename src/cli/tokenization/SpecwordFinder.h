//
// Created by denis on 08.09.20.
//

#ifndef TODOLIST_SPECWORDFINDER_H
#define TODOLIST_SPECWORDFINDER_H

#include "Keyword.h"
#include <string>
#include <memory>

class SpecwordFinder {

public:
    static Keyword     findSpecWord(const std::string_view& input);
};


#endif //TODOLIST_SPECWORDFINDER_H
