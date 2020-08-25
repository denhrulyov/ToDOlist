//
// Created by denis on 19.08.20.
//

#ifndef TODOLIST_PARSETASKNAME_H
#define TODOLIST_PARSETASKNAME_H

#include "ParseTask.h"

class ParseTaskName : public ParseTask {

public:
    explicit
    ParseTaskName(const std::shared_ptr<State>&);

public:
    void                    print(ConsoleContext& context) override;
    void                    execute(ConsoleContext&) override;
    void                    help(ConsoleContext&) override;
};


#endif //TODOLIST_PARSETASKNAME_H
