//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "ParseState.h"

template<class T_next, class T_exit>
class ParseID : public ParseState {

public:
    explicit
    ParseID(const std::shared_ptr<State>&);

public:
    void                print(ConsoleContext& context) override;
    void                execute(ConsoleContext& context) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSEID_H
