//
// Created by denis on 12.07.20.
//

#ifndef EVAL_TASKSTORAGE_H
#define EVAL_TASKSTORAGE_H
#include "memory_model/Task.h"
#include "TaskDTO.h"
#include "memory_model/TaskFactoryInterface.h"
#include <memory>


class TaskFactory : public TaskFactoryInterface {

public:
    Task createTask(const TaskDTO& task_data) override;

};


#endif //EVAL_TASKSTORAGE_H
