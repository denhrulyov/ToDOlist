//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_OSTREAMSERVICESERIALIZER_H
#define TODOLIST_OSTREAMSERVICESERIALIZER_H


#include "ServiceSerializer.h"
#include <iostream>
#include "task.pb.h"

class OstreamServiceSerializer : ServiceSerializer {

public:
    explicit OstreamServiceSerializer(std::ostream& out);

public:
    void serialize(TaskServiceInterface& service) override;

private:
    void serializeSubtasks(TaskProto* task_dump, TaskID id, TaskServiceInterface &service);

private:
    std::ostream& out_;
};


#endif //TODOLIST_OSTREAMSERVICESERIALIZER_H
