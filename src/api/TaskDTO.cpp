//
// Created by denis on 13.07.20.
//

#include "TaskDTO.h"

UserTaskID TaskDTO::getId() {
    return id_;
}

std::string TaskDTO::getName() {
    return task_.name;
}

time_t TaskDTO::getDate() {
    return task_.date;
}

std::string TaskDTO::getLabel() {
    return task_.label;
}

Task::Priority TaskDTO::getPriority() {
    return task_.priority;
}
