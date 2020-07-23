//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKIDCONVERTERINTERFACE_H
#define TODOLIST_TASKIDCONVERTERINTERFACE_H

#include "UserTaskID.h"

class TaskIDConverterInterface {
public:
    virtual TaskID getTaskID(UserTaskID user_id) = 0;
    virtual UserTaskID getUserTaskID(TaskID system_id) = 0;

    virtual ~TaskIDConverterInterface() = default;
};


#endif //TODOLIST_TASKIDCONVERTERINTERFACE_H
