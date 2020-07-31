//
// Created by denis on 31.07.20.
//

#include "TaskStrorage.h"

std::shared_ptr<TaskNode> TaskStrorage::createTask(const Task& task) {
    TaskID generated_id = id_generator_->generateID();
    return std::make_shared<TaskNode>(generated_id, task);
}

void TaskStrorage::eraseTask(TaskID id) {
    nodes_.erase(id);
}

std::shared_ptr<TaskNode> TaskStrorage::getTaskByID(TaskID id) {
    return nodes_[id];
}
