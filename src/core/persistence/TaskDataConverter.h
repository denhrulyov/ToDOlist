//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_TASKDATACONVERTER_H
#define TODOLIST_TASKDATACONVERTER_H

#include "TaskDataConverterInterface.h"

class TaskDataConverter : public TaskDataConverterInterface {

public:
    TaskDTO             RestoreFromMessage(const TaskData& message) override;
    bool                WriteToMessage(const TaskDTO &data, TaskData *message) override;
};

std::unique_ptr<google::protobuf::Timestamp> GetProtobufDate(const BoostDate& date);
BoostDate RestoreDate(const google::protobuf::Timestamp& time_load);
TaskData::Priority GetProtobufPriority(TaskPriority prior);
TaskPriority RestorePriority(TaskData::Priority prior);

#endif //TODOLIST_TASKDATACONVERTER_H
