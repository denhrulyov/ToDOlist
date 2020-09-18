//
// Created by denis on 17.09.20.
//

#include "TaskSerialization.h"


std::unique_ptr<google::protobuf::Timestamp> serialization::serialize_date(const BoostDate& date) {
    using namespace boost::posix_time;
    ptime datetime(date);
    ptime epoch(BoostDate(1970, 1, 1));
    auto timestamp = std::make_unique<google::protobuf::Timestamp>();
    time_t diff_epoch = (datetime - epoch).total_seconds();
    timestamp->set_seconds(diff_epoch);
    return timestamp;
}

BoostDate serialization::deserialize_date(const google::protobuf::Timestamp &time_load) {
    using namespace boost::posix_time;
    ptime datetime = from_time_t(time_load.seconds());
    return datetime.date();
}


TaskProto::Priority serialization::serialize_priority(TaskPriority prior) {
    switch (prior) {
        case TaskPriority::FIRST:
            return TaskProto::FIRST;
        case TaskPriority::SECOND:
            return TaskProto::SECOND;
        case TaskPriority::THIRD:
            return TaskProto::THIRD;
        case TaskPriority::NONE:
            return TaskProto::NONE;
    }
}
TaskPriority serialization::deserialize_priority(TaskProto::Priority prior) {
    switch (prior) {
        case TaskProto::FIRST:
            return TaskPriority::FIRST;
        case TaskProto::SECOND:
            return TaskPriority::SECOND;
        case TaskProto::THIRD:
            return TaskPriority::THIRD;
        case TaskProto::NONE:
            return TaskPriority::NONE;
    }
}

void serialization::serialize_task(const TaskDTO& task, TaskProto* task_dump) {
    task_dump->set_name(task.getName());
    task_dump->set_prior(serialize_priority(task.getPriority()));
    task_dump->set_label(task.getLabel());
    task_dump->set_allocated_date(serialize_date(task.getDate()).release());
    task_dump->set_completed(task.isCompleted());
}

TaskDTO serialization::deserialize_task(const TaskProto& task_load) {
    return TaskDTO::create( TaskID(0),
                            task_load.name(),
                            deserialize_priority(task_load.prior()),
                            task_load.label(),
                            deserialize_date(task_load.date()),
                            task_load.completed());
}
