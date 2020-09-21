//
// Created by denis on 20.09.20.
//

#ifndef TODOLIST_PROTOTASKSERIALIZER_H
#define TODOLIST_PROTOTASKSERIALIZER_H

#include <google/protobuf/timestamp.pb.h>
#include "core/api/TaskDTO.h"
#include "task.pb.h"
#include "Serialization.h"

/*
 * class filling TaskProto with TaskDTO data
 *
 * @author Denis Hrulov
 */
class ProtoTaskSerializer {

public:
    /*
    * @param task proto
    *
    * @return TaskProto with TaskDTO appropriately converted data
    */
    virtual void serializeTo(const TaskDTO& task, TaskProto* task_dump);
};


#endif //TODOLIST_PROTOTASKSERIALIZER_H
