//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_MOCKTASKDATACONVERTER_H
#define TODOLIST_MOCKTASKDATACONVERTER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/persistence/TaskDataConverterInterface.h"

class MockTaskDataConverter : public TaskDataConverterInterface {

public:
    MOCK_METHOD(TaskDTO, RestoreFromMessage, (const TaskData& message), (override));
    MOCK_METHOD(bool   , WriteToMessage, (const TaskDTO &data, TaskData *message), (override));
};


#endif //TODOLIST_MOCKTASKDATACONVERTER_H
