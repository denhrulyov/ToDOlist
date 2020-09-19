//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
#define TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H

#include "IstreamServiceDeserializer.h"
#include "task.pb.h"

class ProtobufIstreamServiceDeserializer : public IstreamServiceDeserializer {

public:
    std::unique_ptr<TaskServiceInterface> deserialize(std::istream&) override;

};


#endif //TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
