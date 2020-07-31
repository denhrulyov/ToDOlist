//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKAPI_H
#define TODOLIST_TASKAPI_H

#include "TaskService.h"
#include "memory_model/DatePriorityView.h"
#include "memory_model/TagPriorityView.h"
#include "memory_model/TaskFactory.h"
#include "memory_model/TaskStrorage.h"
#include "memory_model/TaskIDFactory.h"

// TaskService injector
/*********************/

namespace task_api {

    TaskService createService() {
        auto id_generator = std::make_unique<TaskStrorage>(std::make_unique<TaskIDFactory>());
        auto creator =      std::make_unique<TaskFactory>();
        auto view_time =    std::make_unique<DatePriorityView>();
        auto view_label =   std::make_unique<TagPriorityView>();
        return TaskService(std::move(id_generator), std::move(creator), std::move(view_time), std::move(view_label));
    }

}

#endif //TODOLIST_TASKAPI_H
