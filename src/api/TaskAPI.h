//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKAPI_H
#define TODOLIST_TASKAPI_H

#include "TaskService.h"
#include "memory_model/DatePriorityView.h"
#include "memory_model/TaskFactory.h"

// TaskService injector
/*********************/

namespace task_api {

    TaskService createService() {
        auto id_generator = std::make_unique<TaskIDFactory>(0);
        auto creator =      std::make_unique<TaskFactory>();
        auto view =         std::make_unique<DatePriorityView>();
        return TaskService(std::move(id_generator), std::move(creator), std::move(view));
    }

}

#endif //TODOLIST_TASKAPI_H
