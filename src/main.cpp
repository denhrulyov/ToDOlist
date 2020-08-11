#include <iostream>

#include "api/TaskService.h"
#include "utils/task_io/ConsoleTaskIO.h"
#include "api/Service.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;

int main() {
    auto today = day_clock::local_day();
    TaskService service = service::createService();
    TaskCreationResult id = service.addTask(
            TaskDTO::create("T1", TaskPriority::FIRST, "tag1", today + days(6))
            );
    TaskCreationResult id2 = service.addSubTask(
            id.getCreatedTaskID().value(), TaskDTO::create("T2", TaskPriority::NONE, "tag2", today + days(2))
            );
    TaskCreationResult id3 = service.addSubTask(
            id2.getCreatedTaskID().value(), TaskDTO::create("T3", TaskPriority::THIRD, "tag3", today + days(1))
            );
    service.postponeTask(id2.getCreatedTaskID().value(), today + days(10));
   // service.deleteTask(id3.getCreatedTaskID().value());
    TaskCreationResult id4 = service.addSubTask(
            id2.getCreatedTaskID().value(), TaskDTO::create("T3", TaskPriority::THIRD, "tag3", today + days(20))
    );
    //service.deleteTask(id2.getCreatedTaskID().value());
    service.complete(id.getCreatedTaskID().value());
    //UserTaskID id4 = service.addTask("T5", TaskPriority::FIRST, "tag4", 2020);
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
    //auto tsk = service.getAllWithLabel("tag1");
    auto tsk = service.getThisWeek();
    for (auto ts : tsk) {
        std::cout << ts;
    }
    std::cout << "after delete\n";
    return 0;
}
