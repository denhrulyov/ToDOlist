//
// Created by denis on 06.08.20.
//

#ifndef TODOLIST_REQUESTRESULT_H
#define TODOLIST_REQUESTRESULT_H

#include <string>
#include <optional>
#include "todo_list/memory_model/data/TaskID.h"


/*
 * Class containing info about the result of executing service request.
 *
 * @author Denys Hrulov
 */

class RequestResult {

public:
    /*
     * Creates result representing successful execution.
     *
     * @return RequestResult instance with positive success status and null error message.
     */
    static RequestResult success();

public:
    RequestResult(bool success, const std::optional<std::string>& error_message);

public:

    virtual bool                            getSuccessStatus();
    virtual std::optional<std::string>      getErrorMessage();


private:

    bool                                    success_;
    std::optional<std::string>              error_message_;
};


#endif //TODOLIST_REQUESTRESULT_H
