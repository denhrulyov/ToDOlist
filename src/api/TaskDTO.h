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
    TaskDTO(const Task&);
    TaskDTO(UserTaskID, const Task&);
    TaskDTO(UserTaskID, const std::string& name, Task::Priority, const std::string& label, time_t);
    TaskDTO(            const std::string& name, Task::Priority, const std::string& label, time_t);
    UserTaskID              getId() const ;
    std::string             getName() const ;
    Task::Priority          getPriority() const ;
    std::string             getLabel() const ;
    time_t                  getDate() const ;


private:
    UserTaskID id_;
    std::string name_;
    Task::Priority priority_;
    std::string label_;
    time_t date_;
};


#endif //TODOLIST_TASKDTO_H
