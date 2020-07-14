//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKENTITY_H
#define TODOLIST_TASKENTITY_H

#include "Task.h"

class TaskEntity {

public:
    TaskEntity(uint id_task, const Task& tref) :
    task_(tref), id_(id_task) {}
    uint                getId();
    std::string         getName();
    time_t              getDate();
    std::string         getLabel();
    Task::Priority      getPriority();

private:
    uint id_;
    const Task& task_;
};


#endif //TODOLIST_TASKENTITY_H
