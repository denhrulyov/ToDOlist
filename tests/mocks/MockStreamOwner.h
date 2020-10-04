//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MOCKSTREAMOWNER_H
#define TODOLIST_MOCKSTREAMOWNER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/persistence/StreamOwner.h"


class MockStreamOwner : public StreamOwner {

public:
    MOCK_METHOD(void, SetStream, (std::unique_ptr<std::iostream>), (override));
};


#endif //TODOLIST_MOCKSTREAMOWNER_H
