//
// Created by denis on 20.09.20.
//

#include "ProtoTaskDeserializer.h"

TaskDTO ProtoTaskDeserializer::deserialize(const TaskProto &task_load) {
    return TaskDTO::create( TaskID(0),
                            task_load.name(),
                            serialization::deserialize_priority(task_load.prior()),
                            task_load.label(),
                            serialization::deserialize_date(task_load.date()),
                            task_load.completed());
}
