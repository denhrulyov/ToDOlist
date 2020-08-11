//
// Created by denis on 06.08.20.
//

#ifndef TODOLIST_TASKMODIFICATIONRESULT_H
#define TODOLIST_TASKMODIFICATIONRESULT_H

#include "RequestResult.h"


/*
 * Class containing info about result of executing service request when performing task modification.
 *
 * @author Denys Hrulov
 */
class TaskModificationResult : public RequestResult {

public:
    TaskModificationResult( const std::optional<TaskID>& modified_id,
                            bool success,
                            const std::optional<std::string>& error_message);

public:
    /*
     * Creates result representing successful execution of task modification.
     *
     * @param id of successfully modified task.
     *
     * @return RequestResult instance with id of modified task, positive success status and null error message.
     */
    static TaskModificationResult success(const TaskID &id_modified);
    /*
     * Creates result representing situation when task to modify does not exist in system.
     *
     * @return RequestResult instance with id of null, negative success status and according error message.
     */
    static TaskModificationResult taskNotFound();
    /*
     * Creates result representing situation when error was occurred.
     *
     * @param error message.
     *
     * @return RequestResult instance with id of null, negative success status and error message specified as parameter.
     */
    static TaskModificationResult error(const std::string& message);

public:
    std::optional<TaskID>           getModifiedTaskID();


private:
    std::optional<TaskID>           modified_id_;

};


#endif //TODOLIST_TASKMODIFICATIONRESULT_H
