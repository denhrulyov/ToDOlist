//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKNAME_H
#define TODOLIST_PARSETASKNAME_H

#include "ParseTask.h"

template<class T_next, class T_exit>
class ParseTaskName : public ParseTask {

public:
    explicit
    ParseTaskName();

public:
    void                    print(ConsoleContext& context) override;
    std::shared_ptr<State>                   execute(ConsoleContext&) override;
    void                    help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKNAME_H
