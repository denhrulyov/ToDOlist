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
    auto pnode = std::make_shared<TaskNode>(created_id, Task {} );
    root_task_->addSubtask(pnode);
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
    return pnode;
}


std::vector<uint> TaskController::getAllSubtasks(uint id_parent) {
    std::vector<uint> children;
    __find_all_children(*id_to_node_[id_parent], children);
    return children;
}


void TaskController::eraseNode(uint id_erase) {
    __remove_from_tree(id_erase);
    for (uint id : getAllSubtasks(id_erase)) {
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
    for (auto& child : tnode.getSubtasks()) {
        __find_all_children(*child, buf);
    }
}

void TaskController::__erase_node_references(uint node_id) {
    id_to_node_.erase(node_id);
}

void TaskController::__remove_from_tree(uint id_task) {
    auto ptr_task_node = id_to_node_[id_task];
    auto ptr_parent_node = ptr_task_node->getParent();
    if (ptr_parent_node) {
        auto children_ = ptr_parent_node->getSubtasks();
        for (auto iter = children_.begin(); iter != children_.end(); ++iter) {
            if (iter->get()->getId() == id_task) {
                children_.erase(iter);
                break;
            }
        }
    }
}

TaskController::TaskController() {
    root_task_ = std::make_shared<TaskNode>(0, Task {});
}
