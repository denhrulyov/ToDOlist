//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_STATEFACTORY_H
#define TODOLIST_STATEFACTORY_H

#include "cli/ConsoleIOInterface.h"
#include "StateFactoryInterface.h"
#include "cli/state_machines/utils/LazyInitializer.h"

class StateFactory : public StateFactoryInterface {

public:
    explicit StateFactory(ConsoleIOInterface&);
public:
    std::shared_ptr<State> getInstance(const Of<AddSubTaskState>&) override;
    std::shared_ptr<State> getInstance(const Of<AddTaskState>&) override;
    std::shared_ptr<State> getInstance(const Of<DeleteTaskState>&) override;
    std::shared_ptr<State> getInstance(const Of<InputState<AddTaskState, ParseCommand>>&) override;
    std::shared_ptr<State> getInstance(const Of<InputState<AddSubTaskState, ParseCommand>>&) override;
    std::shared_ptr<State> getInstance(const Of<ParseAddType>&) override;
    std::shared_ptr<State> getInstance(const Of<ParseCommand>&) override;
    std::shared_ptr<State> getInstance(const Of<ParseShowTag>&) override;
    std::shared_ptr<State> getInstance(const Of<ShowState>&) override;
    std::shared_ptr<State> getInstance(const Of<StartState>&) override;
    std::shared_ptr<State> getInstance(const Of<DeleteStateParseID>&) override ;
    std::shared_ptr<State> getInstance(const Of<InputTaskParseID>&) override ;

public:
    template<class T>
    using LazyInitializerPtr = std::unique_ptr<LazyInitializer<State, T>>;

private:
    template<class T>
    const LazyInitializerPtr<T>& getInitializer();

private:
    ConsoleIOInterface& io_;
    std::tuple<
        LazyInitializerPtr<AddSubTaskState>,
        LazyInitializerPtr<AddTaskState>,
        LazyInitializerPtr<DeleteTaskState>,
        LazyInitializerPtr<InputState<AddTaskState, ParseCommand>>,
        LazyInitializerPtr<InputState<AddSubTaskState, ParseCommand>>,
        LazyInitializerPtr<ParseAddType>,
        LazyInitializerPtr<ParseCommand>,
        LazyInitializerPtr<ParseShowTag>,
        LazyInitializerPtr<ShowState>,
        LazyInitializerPtr<StartState>,
        LazyInitializerPtr<DeleteStateParseID>,
        LazyInitializerPtr<InputTaskParseID>
        > states_;
};

#endif //TODOLIST_STATEFACTORY_H
