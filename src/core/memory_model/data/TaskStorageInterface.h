//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKSTORAGEINTERFACE_H
#define TODOLIST_TASKSTORAGEINTERFACE_H

#include "todo_list/memory_model/structure/TaskNode.h"

class TaskStorageInterface {

public:

    enum class Result {
        SUCCESS,
        FAILURE
    };

public:
    virtual Result                      addTask(const std::shared_ptr<TaskNode>&) = 0;
    virtual Result                      eraseTask(TaskID id_erase) = 0;
    virtual std::weak_ptr<TaskNode>     getTaskByID(TaskID id) = 0;

    virtual                             ~TaskStorageInterface() = default;
};


#endif //TODOLIST_TASKSTORAGEINTERFACE_H
