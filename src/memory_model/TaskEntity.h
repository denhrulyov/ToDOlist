//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKENTITY_H
#define TODOLIST_TASKENTITY_H

#include "Task.h"
#include "memory"

class TaskEntity {

public:
    TaskEntity(uint id_task, const std::shared_ptr<Task>& task_) :
    task_(task_), id_(id_task) {}
    uint                getId();
    std::string         getName();
    time_t              getDate();
    std::string         getLabel();
    Task::Priority      getPriority();

private:
    uint id_;
    std::shared_ptr<Task> task_;
};


#endif //TODOLIST_TASKENTITY_H
