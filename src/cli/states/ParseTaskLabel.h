//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKLABEL_H
#define TODOLIST_PARSETASKLABEL_H

#include "ParseTask.h"

template<class T_next, class T_exit>
class ParseTaskLabel : public ParseTask {

public:
    explicit
    ParseTaskLabel();

public:
    void                print(ConsoleContext& context) override;
    std::shared_ptr<State>               execute(ConsoleContext&) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKLABEL_H
