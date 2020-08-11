//
// Created by denis on 28.07.20.
//

#ifndef TODOLIST_TASKCREATIONRESULT_H
#define TODOLIST_TASKCREATIONRESULT_H

#include "RequestResult.h"
#include "memory_model/TaskID.h"

/*
 * Class containing info about the result of executing service request when performing task creation
 *
 * @author Denys Hrulov
 */
class TaskCreationResult : public RequestResult {

public:
    /*
     * Creates result representing successful execution of task creating.
     *
     * @param id of successfully modified task.
     *
     * @return RequestResult instance with id of modified task, positive success status and null error message.
     */
    static TaskCreationResult       success(const TaskID &id_created);
    /*
     * Creates result representing situation when task needed to create the given does not exist in system.
     *
     * @return RequestResult instance with id of null, negative success status and according error message.
     */
    static TaskCreationResult       error(const std::string& message);
    /*
     * Creates result representing situation when error was occurred.
     *
     * @param error message.
     *
     * @return RequestResult instance with id of null, negative success status and error message specified as parameter.
     */
    static TaskCreationResult       taskNotFound();

public:

    std::optional<TaskID>           getCreatedTaskID();

public:

    TaskCreationResult( const std::optional<TaskID>& created_id,
                        bool success,
                        const std::optional<std::string>& error_message);

private:
    std::optional<TaskID>           created_id_;

};


#endif //TODOLIST_TASKCREATIONRESULT_H
