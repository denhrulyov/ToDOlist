//
// Created by denis on 17.09.20.
//

#include "core/api/TODOList.h"
#include "ProtobufIstreamServiceDeserializer.h"
#include "Serialization.h"


ProtobufIstreamServiceDeserializer::ProtobufIstreamServiceDeserializer(
        std::unique_ptr<IstreamProtoFileLoader<TaskServiceProto>> file_loader,
        std::unique_ptr<ProtoTaskDeserializer> task_deserializer)
        :
        file_loader_(std::move(file_loader)),
        task_deserializer_(std::move(task_deserializer))
        {}


bool ProtobufIstreamServiceDeserializer::deserializeSubtasks(TaskID id_parent, const TaskProto& task_load, TaskServiceInterface& service) {
    for (const TaskProto& subtask_load : task_load.subtasks()) {
        TaskCreationResult result = service.addSubTask(id_parent, task_deserializer_->deserialize(subtask_load));
        if (!result.getCreatedTaskID()) {
            return false;
        }
        TaskID id = result.getCreatedTaskID().value();;
        if (subtask_load.completed()) {
            service.complete(id);
        }
        if (!deserializeSubtasks(id, subtask_load, service)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    // all is OK
    return true;
}

std::unique_ptr<TaskServiceInterface> ProtobufIstreamServiceDeserializer::deserialize(std::istream& in) {
    std::optional<TaskServiceProto> maybe_service_load = file_loader_->load(in);
    if (!maybe_service_load) {
        return nullptr;
    }
    TaskServiceProto service_load = maybe_service_load.value();
    auto service = todo_list::createService();
    for (const TaskProto& task_load : service_load.tasks()) {
        TaskCreationResult result = service->addTask(task_deserializer_->deserialize(task_load));
        if (!result.getCreatedTaskID()) {
            return nullptr;
        }
        TaskID id = result.getCreatedTaskID().value();
        if (task_load.completed()) {
            service->complete(id);
        }
        if (!deserializeSubtasks(id, task_load, *service)) {
            // failed to deserialize subtasks hierarchy at any point
           return nullptr;
        }
    }
    return service;
}

