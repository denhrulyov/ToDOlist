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
#include "memory_model/TaskFactory.h"


namespace task_service {
    TaskService create() {
        auto view =         std::make_unique<PriorityView>();
        auto tree =         std::make_unique<TaskController>();
        auto converter =    std::make_unique<TaskIDConverter>(*tree);
        auto creator =      std::make_unique<TaskFactory>();
        return TaskService(std::move(view), std::move(tree), std::move(converter), std::move(creator));
    }

}

#endif //TODOLIST_TASK_SERVICE_H
