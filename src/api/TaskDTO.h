//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include "memory_model/data/Task.h"
#include "memory"
#include "memory_model/data/TaskID.h"


/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Denys Hrulov
 */
class TaskDTO {

public:
    static TaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate);
    static TaskDTO create(const std::string& name, TaskPriority, const std::string& label, BoostDate);
    static TaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate, bool);

private:
    TaskDTO(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate, bool);

public:
    TaskDTO(const TaskDTO&) = default;

public:
    TaskID                  getId() const ;
    std::string             getName() const ;
    TaskPriority            getPriority() const ;
    std::string             getLabel() const ;
    BoostDate               getDate() const ;
    bool                    isCompleted() const ;


private:
    TaskID id_;
    std::string name_;
    TaskPriority priority_;
    std::string label_;
    BoostDate date_;
    bool completed_;
};


#endif //TODOLIST_TASKDTO_H
