//
// Created by denis on 12.07.20.
//

#include "TaskFactory.h"

Task TaskFactory::createTask(const TaskDTO& task_data) {
    return Task {
                    task_data.getName(),
                    task_data.getPriority(),
                    task_data.getLabel(),
                    task_data.getDate()
                };
}

Task TaskFactory::createPostponedTask(const TaskDTO &task_data, time_t new_date) {
    return Task {
                    task_data.getName(),
                    task_data.getPriority(),
                    task_data.getLabel(),
                    new_date
    };
}