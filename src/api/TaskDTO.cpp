//
// Created by denis on 13.07.20.
//

#include "TaskDTO.h"

UserTaskID TaskDTO::getId() const {
    return id_;
}

std::string TaskDTO::getName() const {
    return task_.name;
}

time_t TaskDTO::getDate() const {
    return task_.date;
}

std::string TaskDTO::getLabel() const {
    return task_.label;
}

Task::Priority TaskDTO::getPriority() const {
    return task_.priority;
}
