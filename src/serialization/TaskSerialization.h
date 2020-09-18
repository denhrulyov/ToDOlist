//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_TASKSEREALIZATION_H
#define TODOLIST_TASKSEREALIZATION_H

#include <google/protobuf/timestamp.pb.h>
#include <iostream>
#include "core/api/TaskDTO.h"
#include "task.pb.h"

namespace serialization {

    std::unique_ptr<google::protobuf::Timestamp> serialize_date(const BoostDate& date);

    BoostDate deserialize_date(const google::protobuf::Timestamp& time_load);

    TaskProto::Priority serialize_priority(TaskPriority prior);

    TaskPriority deserialize_priority(TaskProto::Priority prior);

    TaskDTO deserialize_task(const TaskProto& task_load);

    void serialize_task(const TaskDTO& task, TaskProto* task_dump);


}

#endif //TODOLIST_TASKSEREALIZATION_H
