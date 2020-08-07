//
// Created by denis on 31.07.20.
//

#include "TaskStrorage.h"


TaskStrorageInterface::Result::onAdd
TaskStrorage::addTask(const std::shared_ptr<TaskNode> & node) {
    if (nodes_.count(node->getId())) {
        return Result::onAdd::TASK_ALREADY_EXIST;
    }
    nodes_[node->getId()] = node;
    return Result::onAdd::SUCCESS;
}

TaskStrorageInterface::Result::onDelete
TaskStrorage::eraseTask(TaskID id) {
    if (nodes_.count(id) == 0) {
        return Result::onDelete::TASK_NOT_EXIST;
    }
    nodes_.erase(id);
    return Result::onDelete::SUCCESS;
}

std::shared_ptr<TaskNode> TaskStrorage::getTaskByID(TaskID id) {
    return nodes_.count(id) ? nodes_[id] : nullptr;
}



