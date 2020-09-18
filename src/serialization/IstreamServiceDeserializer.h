//
// Created by denis on 17.09.20.
//

#ifndef TODOLIST_ISTREAMSERVICEDESERIALIZER_H
#define TODOLIST_ISTREAMSERVICEDESERIALIZER_H

#include "ServiceDeserializer.h"
#include "task.pb.h"

class IstreamServiceDeserializer : public ServiceDeserializer {

public:
    explicit IstreamServiceDeserializer(std::istream& in);

public:
    std::unique_ptr<TaskServiceInterface> deserialize() override;

private:
    std::istream& in_;
};


#endif //TODOLIST_ISTREAMSERVICEDESERIALIZER_H
