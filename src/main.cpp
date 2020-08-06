#include <iostream>

#include "api/TaskService.h"
#include "task_io/task_io.h"
#include "api/TaskAPI.h"
#include <boost/date_time.hpp>
#include <boost/regex.hpp>

using namespace boost::gregorian;

int main() {
    auto today = day_clock::local_day();
    TaskService service = task_api::createService();
    TaskCreationResult id = service.addTask(
            TaskDTO("T1", Task::Priority::FIRST, "tag1", today + days(2))
            );
    TaskCreationResult id2 = service.addSubTask(
            id.getCreatedTaskID().value(), TaskDTO("T2", Task::Priority::NONE, "tag2", today + days(2))
            );
    TaskCreationResult id3 = service.addSubTask(
            id2.getCreatedTaskID().value(), TaskDTO("T3", Task::Priority::THIRD, "tag3", today + days(1))
            );
    service.postponeTask(id2.getCreatedTaskID().value(), today + days(10));
   // service.deleteTask(id3.getCreatedTaskID().value());
    TaskCreationResult id4 = service.addSubTask(
            id2.getCreatedTaskID().value(), TaskDTO("T3", Task::Priority::THIRD, "tag3", today + days(20))
    );
    service.deleteTask(id2.getCreatedTaskID().value());
    service.complete(id.getCreatedTaskID().value());
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
    auto tsk = service.getAllWithLabel("tag1");
    for (auto ts : tsk) {
        std::cout << ts;
    }
    std::cout << "after delete\n";
    return 0;
}
