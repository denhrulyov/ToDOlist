//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include "memory_model/Task.h"
#include "memory"
#include "memory_model/TaskID.h"
#include "UserTaskID.h"

class TaskDTO {

public:
    TaskDTO(UserTaskID id_task, const Task& task_) :
    task_(task_), id_(id_task) {}
    UserTaskID              getId() const ;
    std::string             getName() const ;
    time_t                  getDate() const ;
    std::string             getLabel() const ;
    Task::Priority          getPriority() const ;

private:
    UserTaskID id_;
    Task task_;
};


#endif //TODOLIST_TASKDTO_H
