//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_SERVICESERIALIZER_H
#define TODOLIST_SERVICESERIALIZER_H

#include "core/api/TaskServiceInterface.h"
class ServiceSerializer {

public:
    virtual void serialize(TaskServiceInterface& service) = 0;
};


#endif //TODOLIST_SERVICESERIALIZER_H
