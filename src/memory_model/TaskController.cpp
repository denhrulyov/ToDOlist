//
// Created by denis on 13.07.20.
//

#include "TaskController.h"


void tie_child_to_parent(std::shared_ptr<TaskNode>& child, std::shared_ptr<TaskNode>& parent) {
    child->setParent(parent);
    parent->addSubtask(child);
}


std::shared_ptr<TaskNode> TaskController::createNode(const Task& tptr) {
    TaskID created_id = id_generator_.generateID();
    auto pnode = std::make_shared<TaskNode>(created_id, tptr);
    registerNode(pnode);
    return pnode;
}

std::weak_ptr<TaskNode> TaskController::createSubNode(TaskID id_parent, const Task& tptr) {
    auto subnode = createNode(tptr);
    auto parent_node = getNodeById(id_parent);
    tie_child_to_parent(subnode, parent_node);
    return subnode;
}

std::weak_ptr<TaskNode> TaskController::createNodeAndAddToRoot(const Task& tptr) {
    auto node = createNode(tptr);
    tie_child_to_parent(node, root_task_);
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
    //std::cout << "id_ : " << id_erase << " / cnt : " << id_to_node_[id_erase].use_count() << std::endl;
    for (TaskID id : ls) {
        eraseNodeReferences(id);
    }
}


//----------------------__dont_touch---methods--------------------------------------


void TaskController::findAllChildren(const TaskNode &tnode, std::vector<TaskID> &buf) {
    buf.push_back(tnode.getId());
    for (auto child : tnode.getSubtasks()) {
        findAllChildren(*id_to_node_[child], buf);
    }
}

void TaskController::eraseNodeReferences(TaskID node_id) {
    if (node_id.getInt()) id_to_node_.erase(node_id);
}

void TaskController::removeFromTree(TaskID id_task) {
    auto ptr_task_node = id_to_node_[id_task];
    auto ptr_parent_node = ptr_task_node->getParent();
    if (ptr_parent_node) {
        ptr_parent_node->eraseSubtask(id_task);
    }
}

TaskController::TaskController() {
    TaskID root_id = id_generator_.generateID();
    root_task_ = std::make_shared<TaskNode>(root_id, Task {});
    id_to_node_[root_id] = root_task_;
}

std::shared_ptr<TaskNode> TaskController::getNodeById(TaskID id_node) {
    return id_to_node_[id_node];
}

void TaskController::registerNode(const std::shared_ptr<TaskNode> &node) {
    id_to_node_[node->getId()] = node;
}
