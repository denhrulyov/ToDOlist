//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGEINTERFACE_H
#define TODOLIST_TASKSTRORAGEINTERFACE_H

#include "TaskNode.h"

class TaskStrorageInterface {

public:
    class Result {

    public:
        enum class onAdd {
            SUCCESS,
            TASK_ALREADY_EXIST
        };
        enum class onDelete {
            SUCCESS,
            TASK_NOT_EXIST
        };
    };

public:
    virtual Result::onAdd               addTask(const std::shared_ptr<TaskNode>&) = 0;
    virtual Result::onDelete            eraseTask(TaskID id_erase) = 0;
    virtual std::shared_ptr<TaskNode>   getTaskByID(TaskID id) = 0;

    virtual                             ~TaskStrorageInterface() = default;
};


#endif //TODOLIST_TASKSTRORAGEINTERFACE_H
