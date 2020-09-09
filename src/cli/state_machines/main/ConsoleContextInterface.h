//
// Created by denis on 04.09.20.
//

#ifndef TODOLIST_CONSOLECONTEXTINTERFACE_H
#define TODOLIST_CONSOLECONTEXTINTERFACE_H

#include "core/api/TaskServiceInterface.h"
#include "cli/ConsoleIOInterface.h"

typedef int32_t TaskNumber;

class ConsoleContextInterface {

public:
    virtual TaskServiceInterface&                   getTaskService() = 0;
    virtual ConsoleIOInterface &                    getIO() = 0;
    virtual std::map<TaskNumber, TaskID>&           getMatchingTablePositionToID() = 0;
    virtual std::map<TaskID, TaskNumber>&           getMatchingIDtoTablePosition() = 0;

public:
    virtual void                                    fillTaskBuffer(const TaskDTO&) = 0;
    virtual std::optional<TaskDTO>                  getTaskBuffer() = 0;
    virtual void                                    fillIDBuffer(TaskID) = 0;
    virtual std::optional<TaskID>                   getBufferedId() const = 0;

    virtual ~ConsoleContextInterface() =    default;
};


#endif //TODOLIST_CONSOLECONTEXTINTERFACE_H
