//
// Created by denis on 11.08.20.
//

#ifndef TODOLIST_LINKMANAGERINTERFACE_H
#define TODOLIST_LINKMANAGERINTERFACE_H

#include "TaskNode.h"

class LinkManagerInterface {

public:
    virtual void linkSubTask(const std::weak_ptr<TaskNode>& main_task, const std::weak_ptr<TaskNode>& sub_task) = 0;
    virtual void setLinks(const std::weak_ptr<TaskNode>& node) = 0;
    virtual void removeLinks(const std::weak_ptr<TaskNode>& node) = 0;
    virtual void moveInboundLinks(const std::weak_ptr<TaskNode>& from, const std::weak_ptr<TaskNode>& to) = 0;

    virtual ~LinkManagerInterface() = default;
};


#endif //TODOLIST_LINKMANAGERINTERFACE_H
