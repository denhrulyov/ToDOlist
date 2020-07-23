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
        auto tree = std::make_unique<TaskController>();
        return TaskService(std::move(view), std::move(tree));
    }

}

#endif //TODOLIST_TASK_SERVICE_H
