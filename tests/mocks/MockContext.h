//
// Created by denis on 09.09.20.
//

#ifndef TODOLIST_MOCKCONTEXT_H
#define TODOLIST_MOCKCONTEXT_H

#include "cli/state_machines/main/ConsoleContextInterface.h"
#include "MockService.h"
#include "MockIO.h"

class MockContext : public ConsoleContextInterface {

public:
    MOCK_METHOD(void, setTaskService, (std::unique_ptr<TaskServiceInterface>), (override));
    MOCK_METHOD(TaskServiceInterface&, getTaskService, () ,(override));
    MOCK_METHOD(ConsoleIOInterface&, getIO, (), (override));
    using from_ID_to_TaskNumber = std::map<TaskNumber, TaskID>;
    MOCK_METHOD(from_ID_to_TaskNumber&, getMatchingTablePositionToID, (), (override));
    using from_TaskNumber_to_ID = std::map<TaskID, TaskNumber>;
    MOCK_METHOD(from_TaskNumber_to_ID&, getMatchingIDtoTablePosition, (), (override));
    MOCK_METHOD(void, fillTaskBuffer, (const TaskDTO&), (override));
    MOCK_METHOD(std::optional<TaskDTO>, getTaskBuffer, () ,(override));
    MOCK_METHOD(void, fillIDBuffer, (TaskID) ,(override));
    MOCK_METHOD(std::optional<TaskID>, getBufferedId, (), (override, const));
    MOCK_METHOD(void, fillTable, (const std::vector<TaskDTO>&), (override));
    MOCK_METHOD(OstreamServiceSerializer&, getSerializer, (), (override));
    MOCK_METHOD(IstreamServiceDeserializer&, getDeserializer, (), (override));
};


#endif //TODOLIST_MOCKCONTEXT_H
