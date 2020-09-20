//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
#define TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H

#include "IstreamServiceDeserializer.h"
#include "ProtoTaskSerializer.h"
#include "ProtoTaskDeserializer.h"
#include "task.pb.h"

class ProtobufIstreamServiceDeserializer : public IstreamServiceDeserializer {

public:
    explicit ProtobufIstreamServiceDeserializer(
            std::unique_ptr<ProtoTaskDeserializer>);

public:
    std::unique_ptr<TaskServiceInterface> deserialize(std::istream&) override;

private:
    bool deserializeSubtasks(TaskID id_parent, const TaskProto& task_load, TaskServiceInterface& service);

private:
    std::unique_ptr<ProtoTaskDeserializer> task_deserializer_;
};


#endif //TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
