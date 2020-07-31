//
// Created by denis on 31.07.20.
//

#include "TaskStrorage.h"

TaskStrorage::TaskStrorage(std::unique_ptr<TaskIDFactoryInterface> id_generator) :
id_generator_(std::move(id_generator)) {}

std::shared_ptr<TaskNode> TaskStrorage::createTask(const Task& task) {
    TaskID generated_id = id_generator_->generateID();
    return nodes_[generated_id] = std::make_shared<TaskNode>(generated_id, task);
}

void TaskStrorage::eraseTask(TaskID id) {
    nodes_.erase(id);
}

std::shared_ptr<TaskNode> TaskStrorage::getTaskByID(TaskID id) {
    return nodes_.count(id) ? nodes_[id] : nullptr;
}

std::shared_ptr<TaskNode> TaskStrorage::recreateTask(TaskID id, const Task& new_data) {
    auto old = nodes_[id];
    auto new_node = std::make_shared<TaskNode>(id, new_data);
    new_node->setParent(old->getParent());
    for (auto child : old->getSubNodes()) {
        new_node->addSubtask(child);
    }
    return nodes_.count(id) ? (nodes_[id] = new_node) : nullptr;
}


