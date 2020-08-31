//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKPRIORITY_H
#define TODOLIST_PARSETASKPRIORITY_H


#include "ParseTask.h"

template<class T_next, class T_exit>
class ParseTaskPriority : public ParseTask {

public:
    explicit
    ParseTaskPriority();

public:

    void                    print(ConsoleContext&) override;
    std::shared_ptr<State>  execute(ConsoleContext&) override;
    void                    help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKPRIORITY_H
