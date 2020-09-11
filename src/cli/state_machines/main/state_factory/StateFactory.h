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
    std::shared_ptr<State> getInstanceOfAddSubTaskState() override;
    std::shared_ptr<State> getInstanceOfAddTaskState() override;
    std::shared_ptr<State> getInstanceOfDeleteTaskState() override;
    std::shared_ptr<State> getInstanceOfSubTaskInputChain() override;
    std::shared_ptr<State> getInstanceOfTaskInputChain() override;
    std::shared_ptr<State> getInstanceOfParseAddType() override;
    std::shared_ptr<State> getInstanceOfParseCommand() override;
    std::shared_ptr<State> getInstanceOfParseShowTag() override;
    std::shared_ptr<State> getInstanceOfShowState() override;
    std::shared_ptr<State> getInstanceOfStartState() override;
    std::shared_ptr<State> getInstanceOfDeleteStateParseID() override;
    std::shared_ptr<State> getInstanceOfInputTaskParseID() override;

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
        LazyInitializerPtr<InputTaskState>,
        LazyInitializerPtr<InputSubTaskState>,
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
