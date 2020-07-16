//
// Created by denis on 13.07.20.
//

#include "TaskEntity.h"

uint TaskEntity::getId() {
    return id_;
}

std::string TaskEntity::getName() {
    return task_->name;
}

time_t TaskEntity::getDate() {
    return task_->date;
}

std::string TaskEntity::getLabel() {
    return task_->label;
}

Task::Priority TaskEntity::getPriority() {
    return task_->priority;
}
