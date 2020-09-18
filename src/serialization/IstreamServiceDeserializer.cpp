//
// Created by denis on 17.09.20.
//

#include "core/api/TODOList.h"
#include "IstreamServiceDeserializer.h"
#include "TaskSerialization.h"

IstreamServiceDeserializer::IstreamServiceDeserializer(std::istream& in) : in_(in) {}

bool deserialize_subtasks(TaskID id_parent, const TaskProto& task_load, TaskServiceInterface& service) {
    for (const TaskProto& subtask_load : task_load.subtasks()) {
        TaskCreationResult result = service.addSubTask(id_parent, serialization::deserialize_task(task_load));
        if (!result.getCreatedTaskID()) {
            return false;
        }
        TaskID id = result.getCreatedTaskID().value();;
        if (subtask_load.completed()) {
            service.complete(id);
        }
        if (!deserialize_subtasks(id, subtask_load, service)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    // all is OK
    return true;
}

std::unique_ptr<TaskServiceInterface> IstreamServiceDeserializer::deserialize() {
    TaskServiceProto service_load;
    if(!service_load.ParseFromIstream(&in_)) {
        return nullptr;
    }
    auto service = todo_list::createService();
    for (const TaskProto& task_load : service_load.tasks()) {
        TaskCreationResult result = service->addTask(serialization::deserialize_task(task_load));
        if (!result.getCreatedTaskID()) {
            return nullptr;
        }
        TaskID id = result.getCreatedTaskID().value();
        if (task_load.completed()) {
            service->complete(id);
        }
        if (!deserialize_subtasks(id, task_load, *service)) {
            // failed to deserialize subtasks hierarchy at any point
           return nullptr;
        }
    }
    return service;
}

