//
// Created by denis on 18.09.20.
//

#include "ServiceSerializer.h"
#include <iostream>
#include "task.pb.h"

class OstreamServiceSerializer : public ServiceSerializer {

public:
    virtual void serialize(TaskServiceInterface& service) = 0;
};