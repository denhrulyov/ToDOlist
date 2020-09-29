//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_CONSOLETASKIO_H
#define TODOLIST_CONSOLETASKIO_H

#include "core/memory_model/api/TaskDTO.h"
#include <unordered_map>
#include <iomanip>


namespace console_task_io {

    const std::unordered_map<TaskPriority, std::string> priorty_repr = {
            {TaskPriority::FIRST, "first"},
            {TaskPriority::SECOND, "second"},
            {TaskPriority::THIRD, "third"},
            {TaskPriority::NONE, "none"},
    };

}

std::ostream& operator << (std::ostream& out, TaskDTO task);





#endif //TODOLIST_CONSOLETASKIO_H
