//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_PRIORITYVIEWINTERFACE_H
#define TODOLIST_PRIORITYVIEWINTERFACE_H

#include "TaskNode.h"

class PriorityViewInterface {

public:
    virtual void addToView(std::weak_ptr<TaskNode>) = 0;
    virtual std::vector<std::weak_ptr<TaskNode>> getAllToDate(time_t) = 0;
    virtual ~PriorityViewInterface() = default;
};


#endif //TODOLIST_PRIORITYVIEWINTERFACE_H
