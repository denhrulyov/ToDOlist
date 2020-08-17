//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_CONSOLETASKIO_H
#define TODOLIST_CONSOLETASKIO_H

#include "core/api/TaskDTO.h"
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

std::ostream& operator << (std::ostream& out, TaskDTO task) {
    out << "Task id_ = " << task.getId() << std::endl;
    out << "  name : " << task.getName() << std::endl;
    out << "  priority : " << console_task_io::priorty_repr.at(task.getPriority()) << std::endl;
    out << "  date : " << task.getDate() << std::endl;
    out << "  label : " << task.getLabel() << std::endl;
    out << "  complete : " << std::boolalpha << task.isCompleted() << std::endl;
    return out;
}





#endif //TODOLIST_CONSOLETASKIO_H
