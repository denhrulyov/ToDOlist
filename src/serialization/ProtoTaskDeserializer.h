//
// Created by denis on 20.09.20.
//

#ifndef TODOLIST_PROTOTASKDESERIALIZER_H
#define TODOLIST_PROTOTASKDESERIALIZER_H

#include <google/protobuf/timestamp.pb.h>
#include "core/api/TaskDTO.h"
#include "task.pb.h"
#include "Serialization.h"

/*
 * class extracting TaskDTO from TaskProto
 *
 * @author Denis Hrulov
 */

class ProtoTaskDeserializer {

public:
    /*
    * @param task proto
    *
    * @return dto with appropriately converted data
    */
    virtual TaskDTO deserialize(const TaskProto& task_load);
};


#endif //TODOLIST_PROTOTASKDESERIALIZER_H
