//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_PRIORITYVIEWINTERFACE_H
#define TODOLIST_PRIORITYVIEWINTERFACE_H

#include "TaskNode.h"

template<class constraint_type>
class PriorityViewInterface {

public:
    virtual void addToView(const std::weak_ptr<TaskNode>&) = 0;
    virtual std::vector<std::weak_ptr<TaskNode>> getAll(const constraint_type& param) = 0;
    virtual ~PriorityViewInterface() = default;
};


#endif //TODOLIST_PRIORITYVIEWINTERFACE_H
