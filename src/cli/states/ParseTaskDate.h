//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_PARSETASKDATE_H
#define TODOLIST_PARSETASKDATE_H

#include "ParseTask.h"

class ParseTaskDate : public ParseTask {

public:
    explicit
    ParseTaskDate(const std::shared_ptr<State>&);

public:
    void                print(ConsoleContext& context) override;
    void                execute(ConsoleContext&) override;
    void                help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKDATE_H
