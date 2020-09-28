//
// Created by denis on 31.07.20.
//

#include "TaskStorage.h"


TaskStorageInterface::Result
TaskStorage::addTask(const std::shared_ptr<TaskNode> & node) {
    if (nodes_.count(node->getId())) {
        return Result::FAILURE;
    }
    nodes_[node->getId()] = node;
    return Result::SUCCESS;
}

TaskStorageInterface::Result
TaskStorage::eraseTask(TaskID id) {
    if (nodes_.count(id) == 0) {
        return Result::FAILURE;
    }
    nodes_.erase(id);
    return Result::SUCCESS;
}

std::weak_ptr<TaskNode> TaskStorage::getTaskByID(TaskID id) {
    return nodes_.count(id) ? nodes_[id] : nullptr;
}

std::vector<std::weak_ptr<TaskNode>> TaskStorage::getAllTasks() {
    std::vector<std::weak_ptr<TaskNode>> result;
    std::transform(nodes_.begin(), nodes_.end(), std::back_inserter(result),
            [] (const auto& item) {
                return item.second;
            });
    return result;
}



