//
// Created by denis on 21.08.20.
//

#ifndef TODOLIST_UTILS_H
#define TODOLIST_UTILS_H

#include "State.h"
#include "core/utils/task_io/ConsoleTaskIO.h"

template <class FirstState>
std::shared_ptr<State> create_chain_impl() {
    return std::make_shared<FirstState>(nullptr);
}

template <class FirstState, class ...RestStates,
        typename std::enable_if<0 < sizeof...(RestStates), int>::type = 0>
std::shared_ptr<State> create_chain_impl() {
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

std::string field_repr(const std::optional<TaskPriority>& field);


#endif //TODOLIST_UTILS_H

