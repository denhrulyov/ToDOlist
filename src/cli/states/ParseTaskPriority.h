//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKPRIORITY_H
#define TODOLIST_PARSETASKPRIORITY_H


#include "ParseTask.h"

class ParseTaskPriority : public ParseTask {

public:
    explicit
    ParseTaskPriority(const std::shared_ptr<State>&);

public:

    void                    print(ConsoleContext&) override;
    std::shared_ptr<State>  execute(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKPRIORITY_H
