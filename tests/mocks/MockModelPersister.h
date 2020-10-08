//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_MOCKPERSISTER_H
#define TODOLIST_MOCKPERSISTER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/persistence/ModelPersister.h"

class MockModelPersister : public ModelPersister {

public:
    MOCK_METHOD(bool, Save, (), (override));
    MOCK_METHOD(bool, Load, (), (override));
};


#endif //TODOLIST_MOCKPERSISTER_H
