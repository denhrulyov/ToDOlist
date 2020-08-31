//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEID_H
#define TODOLIST_PARSEID_H

#include "ParseTask.h"

template<class T_next, class T_exit>
class ParseID : public ParseTask {

public:
    explicit
    ParseID();

public:
    void                        print(ConsoleContext& context) override;
    std::shared_ptr<State>      execute(ConsoleContext& context) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSEID_H
