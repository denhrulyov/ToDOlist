//
// Created by denis on 17.09.20.
//

#include "ProtobufOstreamServiceSerializer.h"
#include "TaskSerialization.h"


std::set<TaskID> find_non_root_tasks(TaskServiceInterface &service) {
    std::set<TaskID> has_parent;
    for (const auto& task : service.getAllTasks()) {
        for (const auto& subtask : service.getSubTasks(task.getId())) {
            // it is subtask thus it has parent
            has_parent.insert(subtask.getId());
        }
    }
    return has_parent;
}

void ProtobufOstreamServiceSerializer::serializeSubtasks(TaskProto* task_dump,
                                                         TaskID id,
                                                         TaskServiceInterface &service) {
    for (const auto& subtask : service.getSubTasks(id)) {
        TaskProto* subtask_dump = task_dump->add_subtasks();
        serialization::serialize_task(subtask, subtask_dump);
        serializeSubtasks(subtask_dump, subtask.getId(), service);
    }
}

void ProtobufOstreamServiceSerializer::serialize(std::ostream& out, TaskServiceInterface &service) {
    TaskServiceProto service_dump;
    std::set<TaskID> has_parent = find_non_root_tasks(service);
    for (const auto& task : service.getAllTasks()) {
        if (has_parent.find(task.getId()) == has_parent.end()) {
            TaskProto* task_dump = service_dump.add_tasks();
            serialization::serialize_task(task, task_dump);
            serializeSubtasks(task_dump, task.getId(), service);
        }
    }
    service_dump.SerializeToOstream(&out);
}

