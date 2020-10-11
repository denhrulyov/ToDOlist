//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MOCKMODELHOLDER_H
#define TODOLIST_MOCKMODELHOLDER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/RepositoryHolder.h"



class MockModelHolder : public RepositoryHolder {

public:
    MockModelHolder() : RepositoryHolder(std::make_unique<RepositoryCreator>(), nullptr) {}
    MOCK_METHOD(TaskRepositoryInterface&, GetModel,(), (override));
    MOCK_METHOD(bool               , LoadModelFromFile, (const std::string& filepath), (override));
    MOCK_METHOD(bool               , SaveModelToFile, (const std::string& filepath), (override));
};


#endif //TODOLIST_MOCKMODELHOLDER_H
