//
// Created by denis on 13.07.20.
//

#include "TaskController.h"


uint TaskController::getNextAvailableId() {
    uint newid = id_to_node_.empty() ?
                 0 :
                 (std::prev(id_to_node_.end())->first + 1);
    return newid;
}





std::shared_ptr<TaskNode> TaskController::createNode(std::unique_ptr<Task> tptr) {
    uint created_id = getNextAvailableId();
    auto pnode = std::make_shared<TaskNode>(created_id, std::move(tptr));
    id_to_node_[created_id] = pnode;
    return pnode;
}

std::weak_ptr<TaskNode> TaskController::createChild(uint id_parent, std::unique_ptr<Task> tptr) {
    auto pnode = createNode(std::move(tptr));
    auto parent_node = id_to_node_[id_parent];
    __bind_parent(&parent_node->getSubtasks(), pnode);
    return pnode;
}

std::weak_ptr<TaskNode> TaskController::createSingleNode(std::unique_ptr<Task> tptr) {
    auto pnode = createNode(std::move(tptr));
    __bind_parent(&task_nodes_, pnode);
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
    node_places_[child->getId()] = std::make_pair(parent_children_list, std::prev(parent_children_list->end()));
}


void TaskController::__find_all_children(const TaskNode &tnode, std::vector<uint> &buf) {
    buf.push_back(tnode.getId());
    for (auto& child : tnode.getSubtasks()) {
        __find_all_children(*child, buf);
    }
}

void TaskController::__erase_node_references(uint node_id) {
    node_places_.erase(node_id);
    id_to_node_.erase(node_id);
}

void TaskController::__remove_from_tree(uint id_task) {
    auto parent_n_child = node_places_[id_task];
    parent_n_child.first->erase(parent_n_child.second);
}
