//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

uint TaskService::addTask(const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    std::shared_ptr<Task> ptask = storage_.createTask(name, priority, label, date);
    std::weak_ptr<TaskNode> pnode = tasks_.createSingleNode(ptask);
    uint created_id = pnode.lock()->getId();
    order_.addToView(pnode);
    return created_id;
}

uint TaskService::addSubTask(uint id_parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    std::shared_ptr<Task> ptask = storage_.createTask(name, priority, label, date);
    std::weak_ptr<TaskNode> pnode = tasks_.createChild(id_parent, ptask);
    uint created_id = pnode.lock()->getId();
    order_.addToView(pnode);
    return created_id;
}

void TaskService::popTask(uint id_task) {
    tasks_.eraseNode(id_task);
}

std::vector<TaskEntity> TaskService::getAllTasks() {
    return order_.getAllToDate(std::numeric_limits<time_t>::max());
}

