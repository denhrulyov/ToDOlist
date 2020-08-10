//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGEINTERFACE_H
#define TODOLIST_TASKSTRORAGEINTERFACE_H

#include "TaskNode.h"

class TaskStrorageInterface {

public:

    enum class Result {
        SUCCESS,
        FAILURE
    };

public:
    virtual Result                      addTask(const std::shared_ptr<TaskNode>&) = 0;
    virtual Result                      eraseTask(TaskID id_erase) = 0;
    virtual std::weak_ptr<TaskNode>     getTaskByID(TaskID id) = 0;

    virtual                             ~TaskStrorageInterface() = default;
};


#endif //TODOLIST_TASKSTRORAGEINTERFACE_H
