//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_PRIORITYVIEWINTERFACE_H
#define TODOLIST_PRIORITYVIEWINTERFACE_H

#include "TaskNode.h"

template<class T>
class PriorityViewInterface {

public:
    virtual void                                    addToView(const std::weak_ptr<TaskNode>&) = 0;
    virtual std::vector<std::weak_ptr<TaskNode>>    getAllWithConstraint(const T& param) = 0;
    virtual std::vector<std::weak_ptr<TaskNode>>    getAllSortedByFirstParam() = 0;
    virtual void                                    removeFromView(TaskID id) = 0;
    virtual ~PriorityViewInterface() =              default;
};


#endif //TODOLIST_PRIORITYVIEWINTERFACE_H
