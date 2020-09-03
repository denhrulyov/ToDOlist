//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_DELETESTATEPARSEID_H
#define TODOLIST_DELETESTATEPARSEID_H

#include "State.h"

class DeleteStateParseID : public State {
public:
    DeleteStateParseID();

public:
    void                        print(ConsoleContext& context) override;
    std::shared_ptr<State>      execute(ConsoleContext& context) override;
    void                        help(ConsoleContext&) override;
};


#endif //TODOLIST_DELETESTATEPARSEID_H
