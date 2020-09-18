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
    explicit ProtobufOstreamServiceSerializer(std::ostream& out);

public:
    void serialize(TaskServiceInterface& service) override;

private:
    void serializeSubtasks(TaskProto* task_dump, TaskID id, TaskServiceInterface &service);

private:
    std::ostream& out_;
};


#endif //TODOLIST_PROTOBUFOSTREAMSERVICESERIALIZER_H
