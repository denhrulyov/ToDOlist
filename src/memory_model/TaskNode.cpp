//
// Created by denis on 10.07.20.
//

#include "TaskNode.h"

Task TaskNode::getTask() const {
    return root_task_;
}


void TaskNode::addSubtask(std::shared_ptr<TaskNode> subtask) {
    subtasks_[subtask->getId()] = subtask;
}

TaskID TaskNode::getId() const {
    return id;
}


std::shared_ptr<TaskNode> TaskNode::getParent() {
    return parent_.lock();
}

void TaskNode::setParent(std::weak_ptr<TaskNode> parent) {
    parent_ = parent;
}

std::vector<TaskID> TaskNode::getSubtasks() const {
    std::vector<TaskID> sub;
    for (const auto& pnode : subtasks_) {
        sub.push_back(pnode.first);
    }
    return sub;
}

void TaskNode::eraseSubtask(TaskID id_erase) {
    subtasks_.erase(id_erase);
}
