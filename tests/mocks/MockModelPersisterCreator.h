//
// Created by denis on 07.10.20.
//

#ifndef TODOLIST_MOCKMODELPERSISTERCREATOR_H
#define TODOLIST_MOCKMODELPERSISTERCREATOR_H


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/persistence/PersisterCreator.h"


class MockModelPersisterCreator : public PersisterCreator {

public:
    MOCK_METHOD(std::unique_ptr<ModelPersister>, CreatePersister,
            (TaskRepositoryInterface&, std::shared_ptr<std::iostream>), (override));
};


#endif //TODOLIST_MOCKMODELPERSISTERCREATOR_H
