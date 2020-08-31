//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKDATE_H
#define TODOLIST_PARSETASKDATE_H

#include "ParseTask.h"
#include "StartState.h"


template<class T_next, class T_exit>
class ParseTaskDate : public ParseTask {

public:
    explicit
    ParseTaskDate();

public:
    void                        print(ConsoleContext& context) override;
    std::shared_ptr<State>      execute(ConsoleContext&) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKDATE_H
