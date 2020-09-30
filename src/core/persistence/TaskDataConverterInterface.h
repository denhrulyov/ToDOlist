//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_TASKDATACONVERTERINTERFACE_H
#define TODOLIST_TASKDATACONVERTERINTERFACE_H

#include "task.pb.h"
#include "core/memory_model/api/TaskModelInterface.h"

class TaskDataConverterInterface {

public:
    virtual TaskDTO     RestoreFromMessage(const TaskData& message) = 0;
    virtual bool        WriteToMessage(const TaskDTO &data, TaskData *message) = 0;
    virtual ~TaskDataConverterInterface() = default;
};


#endif //TODOLIST_TASKDATACONVERTERINTERFACE_H
