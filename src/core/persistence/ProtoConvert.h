//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_PROTOCONVERT_H
#define TODOLIST_PROTOCONVERT_H

#include "core/memory_model/api/RepositoryTaskDTO.h"
#include "core/api/TaskDTO.h"
#include "task.pb.h"

namespace proto_convert {

    RepositoryTaskDTO RestoreFromMessage(const TaskData &message);

    template<class TaskDTO>
    bool WriteToMessage(const TaskDTO &task, TaskData *message);

    std::unique_ptr<google::protobuf::Timestamp> GetProtobufDate(const BoostDate &date);

    BoostDate RestoreDate(const google::protobuf::Timestamp &time_load);

    TaskData::Priority GetProtobufPriority(TaskPriority prior);

    TaskPriority RestorePriority(TaskData::Priority prior);
}

template<class TaskDTO>
bool proto_convert::WriteToMessage(const TaskDTO &task, TaskData *message) {
    message->set_name(task.getName());
    message->set_prior(GetProtobufPriority(task.getPriority()));
    message->set_label(task.getLabel());
    message->set_allocated_date(GetProtobufDate(task.getDate()).release());
    message->set_completed(task.isCompleted());
    return true;
}

#endif //TODOLIST_PROTOCONVERT_H
