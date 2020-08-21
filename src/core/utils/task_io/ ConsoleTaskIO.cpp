//
// Created by denis on 21.08.20.
//
#include "ConsoleTaskIO.h"

std::ostream& operator << (std::ostream& out, TaskDTO task) {
    out << "Task id_ = " << task.getId() << std::endl;
    out << "  name : " << task.getName() << std::endl;
    out << "  priority : " << console_task_io::priorty_repr.at(task.getPriority()) << std::endl;
    out << "  date : " << task.getDate() << std::endl;
    out << "  label : " << task.getLabel() << std::endl;
    out << "  complete : " << std::boolalpha << task.isCompleted() << std::endl;
    return out;
}