//
// Created by denis on 13.07.20.
//

#include "TaskController.h"


uint TaskController::getNextAvailableId() {
    uint newid = id_to_node_.empty() ?
                 1 :
                 (std::prev(id_to_node_.end())->first + 1);
    return newid;
}





std::shared_ptr<TaskNode> TaskController::createNode(const Task& tptr) {
    uint created_id = getNextAvailableId();
    auto pnode = std::make_shared<TaskNode>(created_id, tptr);
    pnode->setParent(root_task_);
    id_to_node_[created_id] = pnode;
    return pnode;
}

std::weak_ptr<TaskNode> TaskController::createChild(uint id_parent, const Task& tptr) {
    auto pnode = createNode(tptr);
    auto parent_node = id_to_node_[id_parent];
    parent_node->addSubtask(pnode);
    pnode->setParent(parent_node);
    id_to_node_[pnode->getId()] = pnode;
    return pnode;
}

std::weak_ptr<TaskNode> TaskController::createSingleNode(const Task& tptr) {
    auto pnode = createNode(tptr);
    root_task_->addSubtask(pnode);
    return pnode;
}


std::vector<uint> TaskController::getAllSubtasks(uint id_parent) {
    std::vector<uint> children;
    __find_all_children(*id_to_node_[id_parent], children);
    return children;
}


void TaskController::eraseNode(uint id_erase) {
    auto ls = getAllSubtasks(id_erase);
    __remove_from_tree(id_erase);
    //std::cout << "id : " << id_erase << " / cnt : " << id_to_node_[id_erase].use_count() << std::endl;
    for (uint id : ls) {
        __erase_node_references(id);
    }
}


//----------------------__dont_touch---methods--------------------------------------

void TaskController::__bind_parent(
        std::list<std::shared_ptr<TaskNode>> * parent_children_list,
        const std::shared_ptr<TaskNode>& child) {
    parent_children_list->push_back(child);
}


void TaskController::__find_all_children(const TaskNode &tnode, std::vector<uint> &buf) {
    buf.push_back(tnode.getId());
    for (auto child : tnode.getSubtasks()) {
        __find_all_children(*id_to_node_[child], buf);
    }
}

void TaskController::__erase_node_references(uint node_id) {
    if (node_id) id_to_node_.erase(node_id);
}

void TaskController::__remove_from_tree(uint id_task) {
    auto ptr_task_node = id_to_node_[id_task];
    auto ptr_parent_node = ptr_task_node->getParent();
    if (ptr_parent_node) {
        ptr_parent_node->eraseSubtask(id_task);
    }
}

TaskController::TaskController() {
    root_task_ = std::make_shared<TaskNode>(0, Task {});
    id_to_node_[0] = root_task_;
}
