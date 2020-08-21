//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_TASKBUFFER_H
#define TODOLIST_TASKBUFFER_H

#include "core/memory_model/data/Task.h"

struct TaskBuffer {


    bool filled() const {
        return
        name_.has_value() &&
        priority_.has_value() &&
        label_.has_value() &&
        date_.has_value();
    }

    void clear() {
        name_       = std::nullopt;
        priority_   = std::nullopt;
        label_      = std::nullopt;
        date_       = std::nullopt;
    }

    std::optional<std::string>      name_;
    std::optional<TaskPriority>     priority_;
    std::optional<std::string>      label_;
    std::optional<BoostDate>        date_;

};

#endif //TODOLIST_TASKBUFFER_H
