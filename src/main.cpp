#include <iostream>

#include "memory_model/TaskService.h"
#include "../src/task_io/task_io.hpp"

int main() {
    TaskService service;
    uint id = service.addTask("T1", Task::Priority::NONE, "tag", 2020);
    uint id2 = service.addSubTask(id, "T2", Task::Priority::SECOND, "tag2", 2021);
    uint id3 = service.addSubTask(id2, "T3", Task::Priority::NONE, "tag3", 2022);
    //service.popTask(id2);

    uint id4 = service.addTask("T5", Task::Priority::FIRST, "tag4", 2020);
    uint id5 = service.addSubTask(id, "T6", Task::Priority::THIRD, "tag5", 2021);
    service.popTask(id5);
    uint id6 = service.addSubTask(id4, "T7", Task::Priority::NONE, "tag6", 2022);
    service.popTask(id);
    auto tsk = service.getAllTasks();
    for (auto ts : tsk) {
        std::cout << ts;
    }
    std::cout << "after delete\n";
    return 0;
}
