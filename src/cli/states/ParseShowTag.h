//
// Created by denis on 25.08.20.
//

#ifndef TODOLIST_PARSESHOWTAG_H
#define TODOLIST_PARSESHOWTAG_H

#include "State.h"

class ParseShowTag : public State {

public:
    explicit
    ParseShowTag(const std::shared_ptr<State>&);

public:
    void                print(ConsoleContext& context) override;
    void                execute(ConsoleContext&) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSESHOWTAG_H
