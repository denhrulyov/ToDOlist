//
// Created by denis on 30.09.20.
//

#include "ProtoConvert.h"

std::unique_ptr<google::protobuf::Timestamp> proto_convert::GetProtobufDate(const BoostDate& date) {
    using namespace boost::posix_time;
    ptime datetime(date);
    ptime epoch(BoostDate(1970, 1, 1));
    auto timestamp = std::make_unique<google::protobuf::Timestamp>();
    time_t diff_epoch = (datetime - epoch).total_seconds();
    timestamp->set_seconds(diff_epoch);
    return timestamp;
}

BoostDate proto_convert::RestoreDate(const google::protobuf::Timestamp &time_load) {
    using namespace boost::posix_time;
    ptime datetime = from_time_t(time_load.seconds());
    return datetime.date();
}


TaskData::Priority proto_convert::GetProtobufPriority(TaskPriority prior) {
    switch (prior) {
        case TaskPriority::FIRST:
            return TaskData::FIRST;
        case TaskPriority::SECOND:
            return TaskData::SECOND;
        case TaskPriority::THIRD:
            return TaskData::THIRD;
        case TaskPriority::NONE:
            return TaskData::NONE;
    }
}
TaskPriority proto_convert::RestorePriority(TaskData::Priority prior) {
    switch (prior) {
        case TaskData::FIRST:
            return TaskPriority::FIRST;
        case TaskData::SECOND:
            return TaskPriority::SECOND;
        case TaskData::THIRD:
            return TaskPriority::THIRD;
        case TaskData::NONE:
            return TaskPriority::NONE;
        default:
            return TaskPriority::NONE;
    }
}

/********************************************************************************/

RepositoryTaskDTO proto_convert::RestoreFromMessage(const TaskData &message) {
    return RepositoryTaskDTO::create(TaskID(0),
                           message.name(),
                           RestorePriority(message.prior()),
                           message.label(),
                           RestoreDate(message.date()),
                           message.completed());
}

bool proto_convert::WriteToMessage(const RepositoryTaskDTO &task, TaskData *message) {
    message->set_name(task.getName());
    message->set_prior(GetProtobufPriority(task.getPriority()));
    message->set_label(task.getLabel());
    message->set_allocated_date(GetProtobufDate(task.getDate()).release());
    message->set_completed(task.isCompleted());
    return true;
}
