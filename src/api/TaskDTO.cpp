//
// Created by denis on 13.07.20.
//

#include "TaskDTO.h"

UserTaskID TaskDTO::getId() const {
    return id_;
}

std::string TaskDTO::getName() const {
    return name_;
}

time_t TaskDTO::getDate() const {
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
                 time_t date) :
        name_(name),
        date_(date),
        label_(label),
        priority_(priority)
        {}

TaskDTO::TaskDTO(UserTaskID id_task,
                 const std::string &name,
                 Task::Priority priority,
                 const std::string &label,
                 time_t date) :
        id_(id_task),
        name_(name),
        date_(date),
        label_(label),
        priority_(priority)
{}

TaskDTO::TaskDTO(UserTaskID id_task, const Task& task_) :
        id_(id_task),
        name_(task_.name),
        date_(task_.date),
        label_(task_.label),
        priority_(task_.priority)
        {}

TaskDTO::TaskDTO(const Task & task_) :
        name_(task_.name),
        date_(task_.date),
        label_(task_.label),
        priority_(task_.priority)
{}
