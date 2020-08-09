//
// Created by denis on 31.07.20.
//

#include "TaskStrorage.h"


TaskStrorageInterface::Result
TaskStrorage::addTask(const std::shared_ptr<TaskNode> & node) {
    if (nodes_.count(node->getId())) {
        return Result::FAILURE;
    }
    nodes_[node->getId()] = node;
    return Result::SUCCESS;
}

TaskStrorageInterface::Result
TaskStrorage::eraseTask(TaskID id) {
    if (nodes_.count(id) == 0) {
        return Result::FAILURE;
    }
    nodes_.erase(id);
    return Result::SUCCESS;
}

std::shared_ptr<TaskNode> TaskStrorage::getTaskByID(TaskID id) {
    return nodes_.count(id) ? nodes_[id] : nullptr;
}



