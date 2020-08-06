//
// Created by denis on 13.07.20.
//

#include "TaskDTO.h"

TaskID TaskDTO::getId() const {
    return id_;
}

std::string TaskDTO::getName() const {
    return name_;
}

Gregorian TaskDTO::getDate() const {
    return date_;
}

std::string TaskDTO::getLabel() const {
    return label_;
}

Task::Priority TaskDTO::getPriority() const {
    return priority_;
}

TaskDTO::TaskDTO(const std::string &name,
                 Task::Priority priority,
                 const std::string &label,
                 Gregorian date) :
        name_(name),
        date_(date),
        label_(label),
        priority_(priority)
        {}

TaskDTO::TaskDTO(TaskID id,
                 const std::string &name,
                 Task::Priority priority,
                 const std::string &label,
                 Gregorian date) :
                 TaskDTO(name, priority, label, date) {
                    id_ = id;
                 }


TaskDTO::TaskDTO(TaskID id,
                 const std::string &name,
                 Task::Priority priority, const std::string &label, Gregorian date,
                 bool comlete) :
        TaskDTO(id, name, priority, label, date) {
            complete_ = comlete;
        }

bool TaskDTO::isComplete() const {
    return complete_;
}
