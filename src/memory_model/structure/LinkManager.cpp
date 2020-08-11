//
// Created by denis on 03.08.20.
//

#include "LinkManager.h"

void LinkManager::linkSubTask(const std::weak_ptr<TaskNode> &main_task,
                              const std::weak_ptr<TaskNode> &sub_task  ) {
    auto shared_sub_task = sub_task.lock();
    auto shared_main_task = main_task.lock();
    if (!shared_sub_task) {
        return;
    }
    shared_sub_task->setParent(main_task);
    if (shared_main_task) {
        shared_main_task->addSubtask(sub_task);
    }
}

void LinkManager::setLinks(const std::weak_ptr<TaskNode> &node) {
    by_time_.addToView(node);
    by_label_.addToView(node);
    auto shared_node = node.lock();
    auto shared_parent = shared_node->getParent().lock();
    if (shared_parent) {
        shared_parent->addSubtask(node);
    }
}

void LinkManager::removeLinks(const std::weak_ptr<TaskNode> &node) {
    auto shared_node = node.lock();
    TaskID id = shared_node->getId();
    by_time_.removeFromView(id);
    by_label_.removeFromView(id);
    auto shared_parent = shared_node->getParent().lock();
    if (shared_parent) {
        if (shared_parent->getSubtaskByID(id).lock()) {
            shared_parent->eraseSubtask(id);
        }
    }
}

void LinkManager::moveInboundLinks(const std::weak_ptr<TaskNode> &from, const std::weak_ptr<TaskNode> &to) {
    auto ptr_from = from.lock();
    for (const auto& subnode : ptr_from->getSubNodes()) {
        subnode.lock()->setParent(to);
    }
    removeLinks(from);
    setLinks(to);
}

LinkManager::LinkManager(PriorityViewInterface<BoostDate>& by_time,
                         PriorityViewInterface<std::string>& by_label)
                                   : by_time_(by_time), by_label_(by_label)
                                   {}


