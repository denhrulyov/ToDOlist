//
// Created by denis on 03.08.20.
//

#include "TaskDTOConverter.h"

Task TaskDTOConverter::getTask(const TaskDTO &dto) {
    return Task::create(dto.getName(), dto.getPriority(), dto.getLabel(), dto.getDate());
}

TaskDTO TaskDTOConverter::getDTO(const std::shared_ptr<TaskNode> &node) {
    const Task& task = node->getTask();
    return TaskDTO(node->getId(), task.getName(), task.getPriority(), task.getLabel(), task.getDate());
}
