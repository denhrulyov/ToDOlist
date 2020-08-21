//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "ParseState.h"

class ParseID : public ParseState {

public:
    explicit
    ParseID(const std::shared_ptr<State>&);

public:
    void                    print(ConsoleContext& context) override;
    std::shared_ptr<State>  execute(ConsoleContext& context) override;
};


#endif //TODOLIST_PARSEID_H
