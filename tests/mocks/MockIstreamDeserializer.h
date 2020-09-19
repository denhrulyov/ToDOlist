//
// Created by denis on 19.09.20.
//

#ifndef TODOLIST_MOCKISTREAMDESERIALIZER_H
#define TODOLIST_MOCKISTREAMDESERIALIZER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "serialization/IstreamServiceDeserializer.h"

class MockIstreamDeserializer : public IstreamServiceDeserializer {

public:
    MOCK_METHOD(std::unique_ptr<TaskServiceInterface>, deserialize, (std::istream&), (override));
};


#endif //TODOLIST_MOCKISTREAMDESERIALIZER_H
