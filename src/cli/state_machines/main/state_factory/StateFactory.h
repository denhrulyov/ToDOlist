//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_STATEFACTORY_H
#define TODOLIST_STATEFACTORY_H

#include "StateFactoryInterface.h"

class StateFactory : public StateFactoryInterface {

public:
    std::shared_ptr<State> getInstance(const Visitor<AddSubTaskState>&) override;
    std::shared_ptr<State> getInstance(const Visitor<AddTaskState>&) override;
    std::shared_ptr<State> getInstance(const Visitor<DeleteTaskState>&) override;
    std::shared_ptr<State> getInstance(const Visitor<InputState<AddTaskState, ParseCommand>>&) override;
    std::shared_ptr<State> getInstance(const Visitor<InputState<AddSubTaskState, ParseCommand>>&) override;
    std::shared_ptr<State> getInstance(const Visitor<ParseAddType>&) override;
    std::shared_ptr<State> getInstance(const Visitor<ParseCommand>&) override;
    std::shared_ptr<State> getInstance(const Visitor<ParseShowTag>&) override;
    std::shared_ptr<State> getInstance(const Visitor<ShowState>&) override;
    std::shared_ptr<State> getInstance(const Visitor<StartState>&) override;
    std::shared_ptr<State> getInstance(const Visitor<DeleteStateParseID>&) override ;
    std::shared_ptr<State> getInstance(const Visitor<InputTaskParseID>&) override ;
};

#endif //TODOLIST_STATEFACTORY_H
