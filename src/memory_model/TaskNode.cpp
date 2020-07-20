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

std::shared_ptr<TaskNode> TaskNode::getNthByDate(std::size_t N) const {
    std::vector<std::pair<time_t, std::shared_ptr<TaskNode>>> nodes;
    for (const auto& id_and_node : subtasks_) {
        const auto& node = id_and_node.second;
        nodes.emplace_back(node->getTask().date, node);
    }
    std::nth_element(nodes.begin(), nodes.begin() + N, nodes.end());
    return (nodes.begin() + N)->second;
}

std::shared_ptr<TaskNode> TaskNode::getSubtaskByID(TaskID id) {
    return subtasks_[id];
}
