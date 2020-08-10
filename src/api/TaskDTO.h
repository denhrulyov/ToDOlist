//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include "memory_model/Task.h"
#include "memory"
#include "memory_model/TaskID.h"

class TaskDTO {

public:
    static TaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, Gregorian);
    static TaskDTO create(        const std::string& name, TaskPriority, const std::string& label, Gregorian);
    static TaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, Gregorian, bool);

private:
    TaskDTO(TaskID, const std::string& name, TaskPriority, const std::string& label, Gregorian, bool);

public:
    TaskDTO(const TaskDTO&) = default;

public:
    TaskID                  getId() const ;
    std::string             getName() const ;
    TaskPriority            getPriority() const ;
    std::string             getLabel() const ;
    Gregorian               getDate() const ;
    bool                    isCompleted() const ;


private:
    TaskID id_;
    std::string name_;
    TaskPriority priority_;
    std::string label_;
    Gregorian date_;
    bool completed_;
};


#endif //TODOLIST_TASKDTO_H
