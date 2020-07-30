//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKAPI_H
#define TODOLIST_TASKAPI_H

#include "TaskService.h"
#include "memory_model/TaskController.h"
#include "memory_model/DatePriorityView.h"
#include "memory_model/TaskFactory.h"

// TaskService injector
/*********************/

namespace task_api {

    TaskService createService() {
        auto view =         std::make_unique<DatePriorityView>();
        auto tree =         std::make_unique<TaskController>();
        auto creator =      std::make_unique<TaskFactory>();
        return TaskService(std::move(view), std::move(tree), std::move(creator));
    }

}

#endif //TODOLIST_TASKAPI_H
