//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGE_H
#define TODOLIST_TASKSTRORAGE_H

#include "TaskStrorageInterface.h"

class TaskStrorage : public TaskStrorageInterface {

public:
    Result                                          addTask(const std::shared_ptr<TaskNode>&) override;
    Result                                          eraseTask(TaskID id) override;
    std::weak_ptr<TaskNode>                         getTaskByID(TaskID id) override;

private:
    std::map<TaskID, std::shared_ptr<TaskNode>>     nodes_;
};


#endif //TODOLIST_TASKSTRORAGE_H
