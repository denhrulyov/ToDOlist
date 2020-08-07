//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKAPI_H
#define TODOLIST_TASKAPI_H

#include "TaskService.h"
#include "memory_model/DatePriorityView.h"
#include "memory_model/TagPriorityView.h"
#include "memory_model/TaskStrorage.h"
#include "memory_model/TaskIDFactory.h"

// TaskService injector
/*********************/

namespace task_api {

    TaskService createService() {
        auto storage =      std::make_unique<TaskStrorage>();
        auto view_time =    std::make_unique<DatePriorityView>();
        auto view_label =   std::make_unique<TagPriorityView>();
        auto handler =      ReferenceHandler(*view_time, *view_label);
        return TaskService(std::move(storage), std::move(view_time), std::move(view_label), handler);
    }

}

#endif //TODOLIST_TASKAPI_H
