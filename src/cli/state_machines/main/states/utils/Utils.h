//
// Created by denis on 21.08.20.
//

#ifndef TODOLIST_UTILS_H
#define TODOLIST_UTILS_H

#include <boost/algorithm/string/split.hpp>
#include "cli/state_machines/main/states/State.h"
#include "core/utils/task_io/ConsoleTaskIO.h"

template <class FirstState>
static std::shared_ptr<State> create_chain_impl() {
    return std::make_shared<FirstState>();
}

template <class FirstState, class ...RestStates,
        typename std::enable_if<0 < sizeof...(RestStates), int>::type = 0>
static std::shared_ptr<State> create_chain_impl() {
    auto tail = create_chain_impl<RestStates...>();
    return std::make_shared<FirstState>(tail);
}


template <class ...States>
std::shared_ptr<State> create_chain() {
    return create_chain_impl<States...>();
}

template<class T>
std::string field_repr(const std::optional<T>& field) {
    std::string result;
    std::stringstream ss;
    if (field.has_value()) {
        ss << field.value();
    } else {
        ss << "### unknown ###";
    }
    ss >> result;
    return result;
}

std::string field_repr(const std::optional<std::string>& field);

std::string field_repr(const std::optional<TaskPriority>& field);

#endif //TODOLIST_UTILS_H

