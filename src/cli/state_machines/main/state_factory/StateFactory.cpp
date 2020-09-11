//
// Created by denis on 03.09.20.
//

#include "StateFactory.h"
#include "cli/state_machines/input_task/ParseStateFactory.h"
#include "Of.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "cli/state_machines/main/states/states.h"

template<class T>
StateFactory::LazyInitializerPtr<T> createInitializer(const typename LazyInitializer<State, T>::Creator& init) {
    return std::make_unique<LazyInitializer<State, T>>(init);
}

StateFactory::StateFactory(ConsoleIOInterface &io)
:
io_(io),
states_ {
    createInitializer<AddSubTaskState>([] () {
        return std::make_shared<AddSubTaskState>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<AddTaskState>([] () {
        return std::make_shared<AddTaskState>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<DeleteTaskState>([] () {
        return std::make_shared<DeleteTaskState>();
    }),
    createInitializer<InputState<AddTaskState, ParseCommand>>([&io] () {
        return std::make_shared<InputState<AddTaskState, ParseCommand>>(
                std::move(
                        std::make_unique<InputTaskStateMachine>(
                                std::make_unique<ParseStateFactory>(),
                                io
                        )
                )
        );
    }),
    createInitializer<InputState<AddSubTaskState, ParseCommand>>([&io] () {
        return std::make_shared<InputState<AddSubTaskState, ParseCommand>>(
                std::move(
                        std::make_unique<InputTaskStateMachine>(
                                std::make_unique<ParseStateFactory>(),
                                io
                        )
                )
        );
    }),
    createInitializer<ParseAddType>([] () {
        return std::make_shared<ParseAddType>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<ParseCommand>([] () {
        return std::make_shared<ParseCommand>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<ParseShowTag>([] () {
        return std::make_shared<ParseShowTag>();
    }),
    createInitializer<ShowState>([] () {
        return std::make_shared<ShowState>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<StartState>([] () {
        return std::make_shared<StartState>();
    }),
    createInitializer<DeleteStateParseID>([] () {
        return std::make_shared<DeleteStateParseID>();
    }),
    createInitializer<InputTaskParseID>([] () {
        return std::make_shared<InputTaskParseID>();
    })
}
{}


std::shared_ptr<State> StateFactory::getInstance(const Of<AddSubTaskState> &) {
    return getInitializer<AddSubTaskState>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<AddTaskState> &) {
    return getInitializer<AddTaskState>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<DeleteTaskState> &) {
    return getInitializer<DeleteTaskState>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<InputState<AddTaskState, ParseCommand>> &) {
    return getInitializer<InputState<AddTaskState, ParseCommand>>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<InputState<AddSubTaskState, ParseCommand>> &) {
    return getInitializer<InputState<AddSubTaskState, ParseCommand>>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<ParseAddType> &) {
    return getInitializer<ParseAddType>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<ParseCommand> &) {
    return getInitializer<ParseCommand>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<ParseShowTag> &) {
    return getInitializer<ParseShowTag>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<ShowState> &) {
    return getInitializer<ShowState>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<StartState> &) {
    return getInitializer<StartState>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<DeleteStateParseID> &) {
    return getInitializer<DeleteStateParseID>()->getValue();
}

std::shared_ptr<State> StateFactory::getInstance(const Of<InputTaskParseID> &) {
    return getInitializer<InputTaskParseID>()->getValue();
}



template<class T>
const StateFactory::LazyInitializerPtr<T>& StateFactory::getInitializer() {
    return std::get<LazyInitializerPtr<T>>(states_);
}

