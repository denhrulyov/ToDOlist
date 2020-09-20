//
// Created by denis on 20.09.20.
//

#include "ProtoTaskSerializer.h"


void ProtoTaskSerializer::serializeTo(const TaskDTO &task, TaskProto *task_dump) {
    task_dump->set_name(task.getName());
    task_dump->set_prior(serialization::serialize_priority(task.getPriority()));
    task_dump->set_label(task.getLabel());
    task_dump->set_allocated_date(serialization::serialize_date(task.getDate()).release());
    task_dump->set_completed(task.isCompleted());
}
