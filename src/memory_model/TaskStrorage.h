//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTRORAGE_H
#define TODOLIST_TASKSTRORAGE_H

#include "TaskStrorageInterface.h"
#include "TaskIDFactoryInterface.h"

class TaskStrorage : public TaskStrorageInterface {

public:
    std::shared_ptr<TaskNode>   createTask(const Task&) override;
    void                        eraseTask(TaskID id) override;
    std::shared_ptr<TaskNode>   getTaskByID(TaskID id) override;

private:
    std::map<TaskID, std::shared_ptr<TaskNode>>             nodes_;
    std::unique_ptr<TaskIDFactoryInterface>                 id_generator_;
};


#endif //TODOLIST_TASKSTRORAGE_H
