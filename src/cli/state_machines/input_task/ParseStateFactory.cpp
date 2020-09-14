//
// Created by denis on 07.09.20.
//

#include "ParseStateFactory.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "cli/state_machines/utils/LazyInitializer.h"

template <class T>
using ThisLazyInitializer = LazyInitializer<ParseState, T>;

template<class T>
std::unique_ptr<ThisLazyInitializer<T>> createThisLazyInitializer() {
    return std::make_unique<ThisLazyInitializer<T>>(ThisLazyInitializer<T>::createDefault());
}

ParseStateFactory::ParseStateFactory()
:
states_ {
    std::move(createThisLazyInitializer<ParseTaskName>()),
    std::move(createThisLazyInitializer<ParseTaskPriority>()),
    std::move(createThisLazyInitializer<ParseTaskLabel>()),
    std::move(createThisLazyInitializer<ParseTaskDate>())
},
current_state_(states_.begin())
{}

std::shared_ptr<ParseState> ParseStateFactory::getNextState() {
    if (current_state_ != states_.end()) {
        return (*(current_state_++))->getValue();
    }
    return nullptr;
}

std::shared_ptr<ParseState> ParseStateFactory::getFirstState() {
    current_state_ = states_.begin();
    return getNextState();
}


