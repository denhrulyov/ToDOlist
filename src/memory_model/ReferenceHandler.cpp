//
// Created by denis on 03.08.20.
//

#include "ReferenceHandler.h"

void ReferenceHandler::linkSubTask( const std::shared_ptr<TaskNode> &main_task,
                                    const std::shared_ptr<TaskNode> &sub_task  ) {
    if (!sub_task) {
        return;
    }
    sub_task->setParent(main_task);
    if (main_task) {
        main_task->addSubtask(sub_task);
    }
}

void ReferenceHandler::setReferences(const std::shared_ptr<TaskNode> &node) {
    by_time_.addToView(node);
    by_label_.addToView(node);
    if (node->getParent()) {
        node->getParent()->addSubtask(node);
    }
}

void ReferenceHandler::removeRefrences(const std::shared_ptr<TaskNode> &node) {
    TaskID id = node->getId();
    by_time_.removeFromView(id);
    by_label_.removeFromView(id);
    auto parent = node->getParent();
    if (parent) {
        if (parent->getSubtaskByID(id)) {
            parent->eraseSubtask(id);
        }
    }
}

void ReferenceHandler::moveInboundRefrences(const std::shared_ptr<TaskNode> &from, const std::shared_ptr<TaskNode> &to) {
    for (const auto& subnode : from->getSubNodes()) {
        subnode->setParent(to);
    }
    removeRefrences(from);
    setReferences(to);
}

ReferenceHandler::ReferenceHandler(PriorityViewInterface<time_t>& by_time,
                                   PriorityViewInterface<std::string>& by_label)
                                   : by_time_(by_time), by_label_(by_label)
                                   {}

void
ReferenceHandler::copyExternalReferences(   const std::shared_ptr<TaskNode> &from,
                                            const std::shared_ptr<TaskNode> &to ) {
    to->setParent(from->getParent());
    for (const auto& child : from->getSubNodes()) {
        to->addSubtask(child);
    }
}


