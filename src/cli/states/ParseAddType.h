//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEADDTYPE_H
#define TODOLIST_PARSEADDTYPE_H

class ConsoleContext;
#include "ParseState.h"

class ParseAddType : public ParseState {

public:
    explicit ParseAddType(const std::shared_ptr<State>&);

public:
    void                    print(ConsoleContext& context) override;
    std::shared_ptr<State>  execute(ConsoleContext& context) override;
};


#endif //TODOLIST_PARSEADDTYPE_H
