//
// Created by denis on 20.07.20.
//

#ifndef TODOLIST_TASKUSERDESCRIPTOR_H
#define TODOLIST_TASKUSERDESCRIPTOR_H

#include "memory_model/TaskNode.h"

class TaskUserDescriptor {

private:
    std::weak_ptr<TaskNode> task_node_;
};


#endif //TODOLIST_TASKUSERDESCRIPTOR_H
