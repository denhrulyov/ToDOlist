//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_MULTIWORDDATATOKENIZER_H
#define TODOLIST_MULTIWORDDATATOKENIZER_H

#include "MultiwordDataTokenizerInterface.h"

class MultiwordDataTokenizer : public MultiwordDataTokenizerInterface {

public:

    Token read(ConsoleIO&) override;
    ~MultiwordDataTokenizer() = default;
};


#endif //TODOLIST_MULTIWORDDATATOKENIZER_H
