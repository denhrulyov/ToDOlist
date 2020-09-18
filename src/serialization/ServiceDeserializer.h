//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_SERVICEDESERIALIZER_H
#define TODOLIST_SERVICEDESERIALIZER_H


#include "core/api/TaskServiceInterface.h"
#include "task.pb.h"

class ServiceDeserializer {

public:
    virtual std::unique_ptr<TaskServiceInterface> deserialize() = 0;
};


#endif //TODOLIST_SERVICEDESERIALIZER_H
