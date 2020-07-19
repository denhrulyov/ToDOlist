//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include "Task.h"
#include "memory"
#include "TaskID.h"

class TaskDTO {

public:
    TaskDTO(TaskID id_task, const Task& task_) :
    task_(task_), id_(id_task) {}
    TaskID              getId();
    std::string         getName();
    time_t              getDate();
    std::string         getLabel();
    Task::Priority      getPriority();

private:
    TaskID id_;
    Task task_;
};


#endif //TODOLIST_TASKDTO_H
