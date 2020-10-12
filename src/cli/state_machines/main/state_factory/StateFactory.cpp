//
// Created by denis on 03.09.20.
//

#include "StateFactory.h"
#include "cli/state_machines/input_task/ParseStateFactory.h"
#include "cli/state_machines/input_task/InputTaskContext.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "cli/state_machines/main/states/states.h"

template<class T>
StateFactory::LazyStateInitializer<T> createInitializer(const typename LazyInitializer<State, T>::Creator& init) {
    return LazyInitializer<State, T>(init);
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
    createInitializer<CompleteState>([] () {
        return std::make_shared<CompleteState>();
    }),
    createInitializer<DeleteTaskState>([] () {
        return std::make_shared<DeleteTaskState>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<InputTaskState>([&io] () {
        return std::make_shared<InputTaskState>(
                std::move(
                        std::make_unique<InputTaskStateMachine>(
                                std::make_unique<ParseStateFactory>(),
                                std::make_unique<InputTaskContext>(io)
                        )
                )
        );
    }),
    createInitializer<InputSubTaskState>([&io] () {
        return std::make_shared<InputSubTaskState>(
                std::move(
                        std::make_unique<InputTaskStateMachine>(
                                std::make_unique<ParseStateFactory>(),
                                std::make_unique<InputTaskContext>(io)
                        )
                )
        );
    }),
    LazyStateInitializer<LoadFromFileState>::createDefault(),
    createInitializer<ParseAddType>([] () {
        return std::make_shared<ParseAddType>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<ParseCommand>([] () {
        return std::make_shared<ParseCommand>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<ParsePostponeDate>([] () {
        return std::make_shared<ParsePostponeDate>();
    }),
    createInitializer<ParseShowTag>([] () {
        return std::make_shared<ParseShowTag>();
    }),
    createInitializer<ParseShowParam>([] () {
        return std::make_shared<ParseShowParam>(std::make_unique<KeywordTokenizer>());
    }),
    createInitializer<PostponeState>([] () {
        return std::make_shared<PostponeState>();
    }),
    LazyStateInitializer<SaveToFileState>::createDefault(),
    createInitializer<StartState>([] () {
        return std::make_shared<StartState>();
    }),
    createInitializer<ShowSubTasksState>([] () {
        return std::make_shared<ShowSubTasksState>();
    }),
    createInitializer<DeleteStateParseID>([] () {
        return std::make_shared<DeleteStateParseID>();
    }),
    createInitializer<InputTaskParseID>([] () {
        return std::make_shared<InputTaskParseID>();
    }),
    createInitializer<ParseCompleteID>([] () {
        return std::make_shared<ParseCompleteID>();
    }),
    createInitializer<ParsePostponeID>([] () {
        return std::make_shared<ParsePostponeID>();
    }),
    createInitializer<ShowSubTasksParseID>([] () {
        return std::make_shared<ShowSubTasksParseID>();
    })
}
{}


std::shared_ptr<State> StateFactory::getInstanceOfAddSubTaskState() {
    return getInitializer<AddSubTaskState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfAddTaskState() {
    return getInitializer<AddTaskState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfDeleteTaskState() {
    return getInitializer<DeleteTaskState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfSubTaskInputChain() {
    return getInitializer<InputSubTaskState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfTaskInputChain() {
    return getInitializer<InputTaskState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParseAddType() {
    return getInitializer<ParseAddType>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParseCommand() {
    return getInitializer<ParseCommand>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParseShowTag() {
    return getInitializer<ParseShowTag>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfShowState() {
    return getInitializer<ParseShowParam>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfStartState() {
    return getInitializer<StartState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfDeleteStateParseID() {
    return getInitializer<DeleteStateParseID>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfInputTaskParseID() {
    return getInitializer<InputTaskParseID>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfCompleteState() {
    return getInitializer<CompleteState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParseCompleteID() {
    return getInitializer<ParseCompleteID>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfPostponeState() {
    return getInitializer<PostponeState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParsePostponeID() {
    return getInitializer<ParsePostponeID>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfParsePostponeDate() {
    return getInitializer<ParsePostponeDate>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfShowSubTasksState() {
    return getInitializer<ShowSubTasksState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfShowSubTasksParseID() {
    return getInitializer<ShowSubTasksParseID>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfLoadFromFileState() {
    return getInitializer<LoadFromFileState>().getValue();
}

std::shared_ptr<State> StateFactory::getInstanceOfSaveToFileState() {
    return getInitializer<SaveToFileState>().getValue();
}

template<class T>
StateFactory::LazyStateInitializer<T> &StateFactory::getInitializer() {
    return std::get<StateFactory::LazyStateInitializer<T>>(states_);
}