//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASK_SERVICE_H
#define TODOLIST_TASK_SERVICE_H

// TaskService injector
/*********************/

#include "TaskService.h"
#include "TaskIDConverter.h"
#include "memory_model/TaskController.h"
#include "memory_model/PriorityView.h"


namespace task_service {
    TaskService create() {
        auto view =         std::make_unique<PriorityView>();
        auto tree =         std::make_unique<TaskController>();
        auto converter =    std::make_unique<TaskIDConverter>(*tree);
        return TaskService(std::move(view), std::move(tree), std::move(converter));
    }

}

#endif //TODOLIST_TASK_SERVICE_H
