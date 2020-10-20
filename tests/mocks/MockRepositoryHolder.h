//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MOCKREPOSITORYHOLDER_H
#define TODOLIST_MOCKREPOSITORYHOLDER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/RepositoryHolder.h"



class MockRepositoryHolder : public RepositoryHolder {

public:
    MockRepositoryHolder() : RepositoryHolder(std::make_unique<RepositoryCreator>(), nullptr) {}
    MOCK_METHOD(TaskRepositoryInterface&, GetRepository, (), (override));
    MOCK_METHOD(bool               , LoadRepositoryFromFile, (const std::string& filepath), (override));
    MOCK_METHOD(bool               , SaveRepositoryToFile, (const std::string& filepath), (override));
};


#endif //TODOLIST_MOCKREPOSITORYHOLDER_H
