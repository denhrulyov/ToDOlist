//
// Created by denis on 18.10.20.
//

#ifndef TODOLIST_REPOSITORYTASKDTO_H
#define TODOLIST_REPOSITORYTASKDTO_H


#include "memory"
#include "core/memory_model/data/TaskID.h"
#include "core/memory_model/data/TaskPriority.h"
#include "boost/date_time.hpp"

using BoostDate = boost::gregorian::date;

/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Denys Hrulov
 */
class RepositoryTaskDTO {

public:
    static RepositoryTaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate);
    static RepositoryTaskDTO create(const std::string& name, TaskPriority, const std::string& label, BoostDate);
    static RepositoryTaskDTO create(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate, bool);

private:
    RepositoryTaskDTO(TaskID, const std::string& name, TaskPriority, const std::string& label, BoostDate, bool);

public:
    RepositoryTaskDTO(const RepositoryTaskDTO&) = default;

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

#endif //TODOLIST_REPOSITORYTASKDTO_H
