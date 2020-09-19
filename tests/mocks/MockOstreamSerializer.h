//
// Created by denis on 19.09.20.
//

#ifndef TODOLIST_MOCKOSTREAMSERIALIZER_H
#define TODOLIST_MOCKOSTREAMSERIALIZER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "serialization/OstreamServiceSerializer.h"

class MockOstreamSerializer : public OstreamServiceSerializer {

public:
    MOCK_METHOD(void, serialize, (std::ostream&, TaskServiceInterface&), (override));
};


#endif //TODOLIST_MOCKOSTREAMSERIALIZER_H
