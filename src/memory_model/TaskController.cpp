//
// Created by denis on 13.07.20.
//

#include "TaskController.h"


void tie_child_to_parent(std::shared_ptr<TaskNode>& child, std::shared_ptr<TaskNode>& parent) {
    child->setParent(parent);
    parent->addSubtask(child);
}

/***********************************************************************************/

std::shared_ptr<TaskNode> TaskController::createFreeNode(TaskID id_newnode, const Task &tptr) {
    auto pnode = std::make_shared<TaskNode>(id_newnode, tptr);
    return pnode;
}

std::shared_ptr<TaskNode> TaskController::createNode(TaskID id_newnode, const Task &tptr) {
    auto pnode = createFreeNode(id_newnode, tptr);
    registerNode(pnode);
    return pnode;
}

std::shared_ptr<TaskNode> TaskController::createNode(const Task& tptr) {
    TaskID created_id = id_generator_.generateID();
    return createNode(created_id, tptr);
}

void TaskController::addNodeTo(TaskID id_parent, std::shared_ptr<TaskNode> p_node) {
    registerNode(p_node);
    auto parent_node = getNodeById(id_parent);
    tie_child_to_parent(p_node, parent_node);
}


std::weak_ptr<TaskNode> TaskController::createSubNode(TaskID id_parent, const Task& tptr) {
    auto subnode = createNode(tptr);
    addNodeTo(id_parent, subnode);
    return subnode;
}

std::weak_ptr<TaskNode> TaskController::createNodeAndAddToRoot(const Task& tptr) {
    auto node = createNode(tptr);
    addNodeTo(root_task_->getId(), node);
    return node;
}


std::vector<TaskID> TaskController::getAllSubtasks(TaskID id_parent) {
    std::vector<TaskID> children;
    findAllChildren(*id_to_node_[id_parent], children);
    return children;
}



void TaskController::eraseNode(TaskID id_erase) {
    auto ls = getAllSubtasks(id_erase);
    removeFromTree(id_erase);
    for (TaskID id : ls) {
        eraseNodeReferences(id);
    }
}


void TaskController::findAllChildren(const TaskNode &tnode, std::vector<TaskID> &buf) {
    buf.push_back(tnode.getId());
    for (auto child : tnode.getSubtasks()) {
        findAllChildren(*id_to_node_[child], buf);
    }
}

void TaskController::eraseNodeReferences(TaskID node_id) {
    if (node_id.getInt()) id_to_node_.erase(node_id);
}

void TaskController::removeFromTree(std::shared_ptr<TaskNode> ptr_task_node) {
    auto ptr_parent_node = ptr_task_node->getParent();
    if (ptr_parent_node) {
        ptr_parent_node->eraseSubtask(ptr_task_node->getId());
    }
}

void TaskController::removeFromTree(TaskID id_task) {
    removeFromTree(id_to_node_[id_task]);
}

TaskController::TaskController() {
    TaskID root_id = id_generator_.generateID();
    root_task_ = std::make_shared<TaskNode>(root_id, Task {});
    id_to_node_[root_id] = root_task_;
}

std::shared_ptr<TaskNode> TaskController::getNodeById(TaskID id_node) const {
    return id_to_node_.at(id_node);
}

void TaskController::registerNode(const std::shared_ptr<TaskNode> &node) {
    id_to_node_[node->getId()] = node;
}

std::shared_ptr<TaskNode> TaskController::getRoot() const {
    return root_task_;
}

void TaskController::modifyTaskData(TaskID id_modify, const Task& new_data) {
    auto old_node = getNodeById(id_modify);
    TaskID id_parent = old_node->getParent()->getId();
    auto new_node = old_node->clone(new_data);
    for (const auto& p_child : new_node->getSubNodes()) {
        p_child->setParent(new_node);
    }
    addNodeTo(id_parent, new_node);
    old_node->disconnect();
}
