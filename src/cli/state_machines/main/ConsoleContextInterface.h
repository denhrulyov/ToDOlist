//
// Created by denis on 04.09.20.
//

#ifndef TODOLIST_CONSOLECONTEXTINTERFACE_H
#define TODOLIST_CONSOLECONTEXTINTERFACE_H

#include "core/api/TaskServiceInterface.h"
#include "serialization/IstreamServiceDeserializer.h"
#include "serialization/OstreamServiceSerializer.h"
#include "cli/ConsoleIOInterface.h"

typedef int32_t TaskNumber;


/*
 * Class containing data for TodoList cli
 *
 * @author Denis Hrulov
 */
class ConsoleContextInterface {

public:
    /*
     * @param TaskService to put into context
     */
    virtual void                                    setTaskService(std::unique_ptr<TaskServiceInterface>) = 0;
    /*
     * @return reference to TaskService
     */
    virtual TaskServiceInterface&                   getTaskService() = 0;
    /*
     * @return reference to input-output object
     */
    virtual ConsoleIOInterface &                    getIO() = 0;
    /*
     * @return matching from task position in table to its ID in service
     */
    virtual std::map<TaskNumber, TaskID>&           getMatchingTablePositionToID() = 0;
    /*
     * @return matching from task ID in service to its position in table
     */
    virtual std::map<TaskID, TaskNumber>&           getMatchingIDtoTablePosition() = 0;

public:
    /*
     * sets fields of task buffer to specified in param
     *
     * @param DTO representing task fields
     */
    virtual void                                    fillTaskBuffer(const TaskDTO&) = 0;
    /*
     * @returns dto with buffered data if it was set or nullopt otherwise
     */
    virtual std::optional<TaskDTO>                  getTaskBuffer() = 0;
    /*
     * sets ID buffer to specified in param
     *
     * @param DTO representing task id
     */
    virtual void                                    fillIDBuffer(TaskID) = 0;
    /*
     * @return id of buffered data if it was set or nullopt otherwise
     */
    virtual std::optional<TaskID>                   getBufferedId() const = 0;
    /*
     * @return serialization destination
     */
    virtual OstreamServiceSerializer&               getSerializer() = 0;
    /*
     * @return deserialization source
     */
    virtual IstreamServiceDeserializer&             getDeserializer() = 0;

public:
    /*
     * recreates table of tasks by given task list
     *
     * @param vector of task dto to fill table of tasks
     */
    virtual void                                    fillTable(const std::vector<TaskDTO>&) = 0;

    virtual ~ConsoleContextInterface() =    default;
};


#endif //TODOLIST_CONSOLECONTEXTINTERFACE_H
