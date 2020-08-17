//
// Created by denis on 06.08.20.
//

#ifndef TODOLIST_TASKMODIFICATIONRESULT_H
#define TODOLIST_TASKMODIFICATIONRESULT_H

#include "RequestResult.h"


/*
 * Class containing info about the result of executing service request when performing task modification.
 *
 * @author Denys Hrulov
 */
class TaskModificationResult : public RequestResult {

public:
    TaskModificationResult( bool success,
                            const std::optional<std::string>& error_message);

public:
    /*
     * Creates result representing successful execution of task modification.
     *
     * @return RequestResult instance with positive success status and null error message.
     */
    static TaskModificationResult success();
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

};


#endif //TODOLIST_TASKMODIFICATIONRESULT_H
