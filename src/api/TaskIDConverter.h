//
// Created by denis on 20.07.20.
//

#ifndef TODOLIST_TASKIDCONVERTER_H
#define TODOLIST_TASKIDCONVERTER_H

#include "memory_model/TaskController.h"
#include "UserTaskID.h"

class TaskIDConverter {
public:
    explicit TaskIDConverter(const TaskControllerInterface& ref_tree) : ref_tree_(ref_tree) {}

public:
    TaskID getTaskID(UserTaskID user_id);
    UserTaskID getUserTaskID(TaskID system_id);

private:

    const TaskControllerInterface& ref_tree_;
};


#endif //TODOLIST_TASKIDCONVERTER_H
