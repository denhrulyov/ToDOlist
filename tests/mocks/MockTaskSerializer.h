//
// Created by denis on 21.09.20.
//

#ifndef TODOLIST_MOCKTASKSERIALIZER_H
#define TODOLIST_MOCKTASKSERIALIZER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "serialization/ProtoTaskSerializer.h"

class MockTaskSerializer : public ProtoTaskSerializer {

public:
    MOCK_METHOD(void, serializeTo, (const TaskDTO&, TaskProto*), (override));
};


#endif //TODOLIST_MOCKTASKSERIALIZER_H
