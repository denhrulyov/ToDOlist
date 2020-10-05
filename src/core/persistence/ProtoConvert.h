//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_PROTOCONVERT_H
#define TODOLIST_PROTOCONVERT_H

#include "core/memory_model/api/TaskDTO.h"
#include "task.pb.h"

namespace proto_convert {

    TaskDTO RestoreFromMessage(const TaskData &message);

    bool WriteToMessage(const TaskDTO &data, TaskData *message);

    std::unique_ptr<google::protobuf::Timestamp> GetProtobufDate(const BoostDate &date);

    BoostDate RestoreDate(const google::protobuf::Timestamp &time_load);

    TaskData::Priority GetProtobufPriority(TaskPriority prior);

    TaskPriority RestorePriority(TaskData::Priority prior);
}

#endif //TODOLIST_PROTOCONVERT_H
