//
// Created by denis on 10.07.20.
//

#include "TaskNode.h"
#include <memory>


/*************************************/


Task TaskNode::getTask() const {
    return root_task_;
}


void TaskNode::addSubtask(std::shared_ptr<TaskNode> subtask) {
    subtasks_[subtask->getId()] = subtask;
}

TaskID TaskNode::getId() const {
    return id;
}


std::shared_ptr<TaskNode> TaskNode::getParent() const {
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

std::vector<std::shared_ptr<TaskNode>> TaskNode::getSubNodes() const {
    std::vector<std::shared_ptr<TaskNode>> sub;
    for (const auto& pnode : subtasks_) {
        sub.push_back(pnode.second);
    }
    return sub;
}


void TaskNode::eraseSubtask(TaskID id_erase) {
    subtasks_.erase(id_erase);
}


std::shared_ptr<TaskNode> TaskNode::getSubtaskByID(TaskID id) {
    return subtasks_[id];
}



std::shared_ptr<TaskNode> TaskNode::clone(const Task& new_data) {
    auto this_modified = std::make_shared<TaskNode>(id, new_data, subtasks_);
    this_modified->complete_ = complete_;
    this_modified->parent_ = parent_;
    return this_modified;
}

void TaskNode::complete() {
    complete_ = true;
}

bool TaskNode::isComplete() const {
    return complete_;
}


