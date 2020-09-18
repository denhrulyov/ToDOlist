//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
#define TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H

#include "IstreamServiceDeserializer.h"
#include "task.pb.h"

class ProtobufIstreamServiceDeserializer : public IstreamServiceDeserializer {

public:
    explicit ProtobufIstreamServiceDeserializer(std::istream& in);

public:
    std::unique_ptr<TaskServiceInterface> deserialize() override;

private:
    std::istream& in_;
};


#endif //TODOLIST_PROTOBUFISTREAMSERVICEDESERIALIZER_H
