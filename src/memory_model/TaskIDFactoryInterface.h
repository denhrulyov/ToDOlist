//
// Created by denis on 31.07.20.
//

#ifndef TODOLIST_TASKIDFACTORYINTERFACE_H
#define TODOLIST_TASKIDFACTORYINTERFACE_H

#include "TaskID.h"

class TaskIDFactoryInterface {

public:
    virtual TaskID generateID() = 0;
    virtual ~TaskIDFactoryInterface() = default;
};


#endif //TODOLIST_TASKIDFACTORYINTERFACE_H
