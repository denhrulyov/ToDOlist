//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_PROTOBUFOSTREAMSERVICESERIALIZER_H
#define TODOLIST_PROTOBUFOSTREAMSERVICESERIALIZER_H


#include "OstreamServiceSerializer.h"
#include <iostream>
#include "task.pb.h"

class ProtobufOstreamServiceSerializer : public OstreamServiceSerializer {

public:
    void serialize(std::ostream&, TaskServiceInterface& service) override;

private:
    void serializeSubtasks(TaskProto* task_dump, TaskID id, TaskServiceInterface &service);

};


#endif //TODOLIST_PROTOBUFOSTREAMSERVICESERIALIZER_H
