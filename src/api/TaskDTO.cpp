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

BoostDate TaskDTO::getDate() const {
    return date_;
}

std::string TaskDTO::getLabel() const {
    return label_;
}

TaskPriority TaskDTO::getPriority() const {
    return priority_;
}


TaskDTO::TaskDTO(TaskID id,
                 const std::string &name,
                 TaskPriority priority, const std::string &label, BoostDate date,
                 bool completed)
                :
    id_(id),
    name_(name),
    priority_(priority),
    label_(label),
    date_(date),
    completed_(completed)
{}

TaskDTO
TaskDTO::create(const std::string &name,
                TaskPriority priority,
                const std::string &label,
                BoostDate date)
{
    return TaskDTO(TaskID(), name, priority, label, date, false);
}

TaskDTO
TaskDTO::create(TaskID id,
                const std::string &name,
                TaskPriority priority,
                const std::string &label,
                BoostDate date)
{
    return TaskDTO(id, name, priority, label, date, false);
}


TaskDTO
TaskDTO::create(TaskID id,
                const std::string &name,
                TaskPriority priority, const std::string &label, BoostDate date,
                bool completed)
{
    return TaskDTO(id, name, priority, label, date, completed);
}

bool TaskDTO::isCompleted() const {
    return completed_;
}
