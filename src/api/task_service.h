//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASK_SERVICE_H
#define TODOLIST_TASK_SERVICE_H

// TaskService injector
/*********************/

#include "TaskService.h"
#include "memory_model/PriorityView.h"
#include "memory_model/PriorityViewInterface.h"

namespace task_service {
    TaskService create() {
        auto view = std::make_unique<PriorityView>();
        return TaskService(std::move(view));
    }

}

#endif //TODOLIST_TASK_SERVICE_H
