//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

uint TaskService::addTask(const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_.createNodeAndAddToRoot(ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    uint created_id = created_node.lock()->getId();
    return created_id;
}

uint TaskService::addSubTask(uint id_parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_.createSubNode(id_parent, ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    uint created_id = created_node.lock()->getId();
    return created_id;
}

void TaskService::popTask(uint id_task) {
    task_tree_.eraseNode(id_task);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    return by_priority_.getAllToDate(std::numeric_limits<time_t>::max());
}

