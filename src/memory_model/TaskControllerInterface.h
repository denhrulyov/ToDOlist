//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKCONTROLLERINTERFACE_H
#define TODOLIST_TASKCONTROLLERINTERFACE_H

#include "TaskNode.h"

class TaskControllerInterface {
public:
    virtual std::vector<TaskID>                            getAllSubtasks(TaskID id_parent) = 0;
    virtual std::shared_ptr<TaskNode>                      getNodeById(TaskID id_node) const = 0;
    virtual std::shared_ptr<TaskNode>                      getRoot() const = 0;

public:

    virtual std::weak_ptr<TaskNode>       createSubNode(TaskID id_parent, const Task& tptr) = 0;
    virtual std::weak_ptr<TaskNode>       createNodeAndAddToRoot(const Task& tptr) = 0;
    virtual void                          modifyTaskData(TaskID id_modify, const Task& new_data) = 0;
    virtual void                          eraseNode(TaskID id_erase) = 0;

public:
    virtual ~TaskControllerInterface() = default;
};


#endif //TODOLIST_TASKCONTROLLERINTERFACE_H
