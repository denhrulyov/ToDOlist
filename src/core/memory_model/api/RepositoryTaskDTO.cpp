//
// Created by denis on 13.07.20.
//

#include "RepositoryTaskDTO.h"

TaskID RepositoryTaskDTO::getId() const {
    return id_;
}

std::string RepositoryTaskDTO::getName() const {
    return name_;
}

BoostDate RepositoryTaskDTO::getDate() const {
    return date_;
}

std::string RepositoryTaskDTO::getLabel() const {
    return label_;
}

TaskPriority RepositoryTaskDTO::getPriority() const {
    return priority_;
}


RepositoryTaskDTO::RepositoryTaskDTO(TaskID id,
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

RepositoryTaskDTO
RepositoryTaskDTO::create(const std::string &name,
                          TaskPriority priority,
                          const std::string &label,
                          BoostDate date)
{
    return RepositoryTaskDTO(TaskID(), name, priority, label, date, false);
}

RepositoryTaskDTO
RepositoryTaskDTO::create(TaskID id,
                          const std::string &name,
                          TaskPriority priority,
                          const std::string &label,
                          BoostDate date)
{
    return RepositoryTaskDTO(id, name, priority, label, date, false);
}


RepositoryTaskDTO
RepositoryTaskDTO::create(TaskID id,
                          const std::string &name,
                          TaskPriority priority, const std::string &label, BoostDate date,
                          bool completed)
{
    return RepositoryTaskDTO(id, name, priority, label, date, completed);
}

bool RepositoryTaskDTO::isCompleted() const {
    return completed_;
}
