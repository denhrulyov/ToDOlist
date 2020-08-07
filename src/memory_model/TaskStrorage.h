//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGE_H
#define TODOLIST_TASKSTRORAGE_H

#include "TaskStrorageInterface.h"

class TaskStrorage : public TaskStrorageInterface {



public:
    Result::onAdd                                   addTask(const std::shared_ptr<TaskNode>&) override;
    Result::onDelete                                eraseTask(TaskID id) override;
    std::shared_ptr<TaskNode>                       getTaskByID(TaskID id) override;

private:
    std::map<TaskID, std::shared_ptr<TaskNode>>     nodes_;
};


#endif //TODOLIST_TASKSTRORAGE_H
