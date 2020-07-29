//
// Created by denis on 29.07.20.
//

#ifndef TODOLIST_TAGPRIORITYVIEWINTERFACE_H
#define TODOLIST_TAGPRIORITYVIEWINTERFACE_H

#include "TaskNode.h"

class TagPriorityViewInterface {

public:
    virtual void addToView(const std::weak_ptr<TaskNode>&) = 0;
    virtual std::vector<std::weak_ptr<TaskNode>> getAllWithTag(const std::string& tag) = 0;
    virtual ~TagPriorityViewInterface() = default;
};


#endif //TODOLIST_TAGPRIORITYVIEWINTERFACE_H
