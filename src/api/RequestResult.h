//
// Created by denis on 06.08.20.
//

#ifndef TODOLIST_REQUESTRESULT_H
#define TODOLIST_REQUESTRESULT_H

#include <string>
#include <optional>
#include "memory_model/TaskID.h"

class RequestResult {
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
