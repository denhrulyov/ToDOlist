#include <iostream>

#include "api/TaskService.h"
#include "task_io/task_io.h"
#include "api/task_service.h"

int main() {
    TaskService service = task_service::create();
    UserTaskID id = service.addTask(TaskDTO(UserTaskID ({}), Task
    {"T1", Task::Priority::FIRST, "tag1", 2020}));
    UserTaskID id2 = service.addSubTask(TaskDTO(id, Task
    {"T2", Task::Priority::NONE, "tag2", 2021}));
    UserTaskID id3 = service.addSubTask(TaskDTO(id2, Task
    {"T3", Task::Priority::THIRD, "tag3", 2022}));
    service.deleteTask(TaskID(1));
    //UserTaskID id4 = service.addTask("T5", Task::Priority::FIRST, "tag4", 2020);
    /*service.inspectRoot();
    //service.deleteTask(id2);
    service.inspectRoot();
    UserTaskID id4 = service.addTask(<#initializer#>);
    service.inspectRoot();
    UserTaskID id5 = service.addSubTask(<#initializer#>);
    service.inspectRoot();
    //service.deleteTask(id5);
    service.inspectRoot();
    UserTaskID id6 = service.addSubTask(<#initializer#>);
    service.inspectRoot();
    //service.deleteTask(id);
    service.inspectRoot();
    UserTaskID id7 = service.addSubTask(<#initializer#>);
    service.inspectRoot();
     */
    auto tsk = service.getAllTasks();
    for (auto ts : tsk) {
        std::cout << ts;
    }
    std::cout << "after delete\n";
    return 0;
}
