//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGEINTERFACE_H
#define TODOLIST_TASKSTRORAGEINTERFACE_H

#include "TaskNode.h"

class TaskStrorageInterface {

public:
    virtual std::shared_ptr<TaskNode>   createTask(const Task&) = 0;
    virtual void                        eraseTask(TaskID id_erase) = 0;
    virtual std::shared_ptr<TaskNode>   getTaskByID(TaskID id) = 0;

    virtual                             ~TaskStrorageInterface() = default;
};


#endif //TODOLIST_TASKSTRORAGEINTERFACE_H
