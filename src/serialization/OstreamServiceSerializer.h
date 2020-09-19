//
// Created by denis on 18.09.20.
//

#ifndef TODOLIST_OSTREAMSERVICESERIALIZER_H
#define TODOLIST_OSTREAMSERVICESERIALIZER_H

#include "ServiceSerializer.h"
#include <iostream>
#include "task.pb.h"

class OstreamServiceSerializer {

public:
    virtual void serialize(std::ostream&, TaskServiceInterface& service) = 0;
    virtual ~OstreamServiceSerializer() = default;

};

#endif