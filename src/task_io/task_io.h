//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASK_IO_H
#define TODOLIST_TASK_IO_H

#include "api/TaskDTO.h"
#include <unordered_map>
#include <iomanip>


namespace task_io {

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
    out << "  priority : " << task_io::priorty_repr.at(task.getPriority()) << std::endl;
    out << "  date : " << task.getDate() << std::endl;
    out << "  label : " << task.getLabel() << std::endl;
    out << "  complete : " << std::boolalpha << task.isCompleted() << std::endl;
    return out;
}





#endif //TODOLIST_TASK_IO_H
