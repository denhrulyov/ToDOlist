//
// Created by denis on 10.07.20.
//

#include "TaskNode.h"

Task TaskNode::getTask() const {
    return root_task_;
}

std::list<std::shared_ptr<TaskNode>>& TaskNode::getSubtasks() {
    return subtasks_;
}

void TaskNode::addSubtask(std::shared_ptr<TaskNode> subtask) {
    subtasks_.push_back(subtask);
}

uint TaskNode::getId() const {
    return id;
}

const std::list<std::shared_ptr<TaskNode>> &TaskNode::getSubtasks() const {
    return subtasks_;
}

std::shared_ptr<TaskNode> TaskNode::getParent() {
    return parent_;
}

void TaskNode::setParent(const std::shared_ptr<TaskNode>& parent) {
    parent_ = parent;
}
