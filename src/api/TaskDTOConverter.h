//
// Created by denis on 03.08.20.
//

#ifndef TODOLIST_TASKDTOCONVERTER_H
#define TODOLIST_TASKDTOCONVERTER_H

#include "TaskDTO.h"
#include "memory_model/Task.h"
#include "memory_model/TaskNode.h"

class TaskDTOConverter {

public:
    static Task     getTask(const TaskDTO& dto);
    static TaskDTO  getDTO(const std::shared_ptr<TaskNode>& node);
};


#endif //TODOLIST_TASKDTOCONVERTER_H
