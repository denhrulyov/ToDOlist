//
// Created by denis on 17.09.20.
//

#include "Serialization.h"


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
