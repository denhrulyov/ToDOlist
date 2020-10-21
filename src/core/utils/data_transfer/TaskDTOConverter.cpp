//
// Created by denis on 03.08.20.
//

#include "TaskDTOConverter.h"

Task TaskDTOConverter::getTask(const RepositoryTaskDTO &dto) {
    return Task::create(dto.getName(), dto.getPriority(), dto.getLabel(), dto.getDate());
}

RepositoryTaskDTO TaskDTOConverter::getDTO(const std::shared_ptr<TaskNode> &node) {
    const Task& task = node->getTask();
    return RepositoryTaskDTO::create(
                    node->getId(),
                    task.getName(),
                    task.getPriority(),
                    task.getLabel(),
                    task.getDate(),
                    node->isComplete());
}

