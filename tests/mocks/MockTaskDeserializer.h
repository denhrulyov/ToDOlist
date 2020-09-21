//
// Created by denis on 21.09.20.
//

#ifndef TODOLIST_MOCKTASKDESERIALIZER_H
#define TODOLIST_MOCKTASKDESERIALIZER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "serialization/ProtoTaskDeserializer.h"

class MockTaskDeserializer : public ProtoTaskDeserializer {

public:
    MOCK_METHOD(TaskDTO, deserialize, (const TaskProto&), (override));
};


#endif //TODOLIST_MOCKTASKDESERIALIZER_H
