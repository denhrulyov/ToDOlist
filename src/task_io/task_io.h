//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASK_IO_H
#define TODOLIST_TASK_IO_H

#include "api/TaskDTO.h"
#include <unordered_map>


namespace task_io {

    const std::unordered_map<Task::Priority, std::string> priorty_repr = {
            {Task::Priority::FIRST, "first"},
            {Task::Priority::SECOND, "second"},
            {Task::Priority::THIRD, "third"},
            {Task::Priority::NONE, "none"},
    };

}

std::ostream& operator << (std::ostream& out, TaskDTO task) {
    out << "Task id_ = " << task.getId() << std::endl;
    out << "  name : " << task.getName() << std::endl;
    out << "  priority : " << task_io::priorty_repr.at(task.getPriority()) << std::endl;
    out << "  date : " << task.getDate() << std::endl;
    out << "  label : " << task.getLabel() << std::endl;
    return out;
}





#endif //TODOLIST_TASK_IO_H
