//
// Created by denis on 28.07.20.
//

#ifndef TODOLIST_TASKCREATIONRESULT_H
#define TODOLIST_TASKCREATIONRESULT_H

#include <optional>
#include "memory_model/TaskID.h"

class TaskCreationResult {

public:
    static TaskCreationResult success(const TaskID &id_created);
    static TaskCreationResult taskNotFound();

public:

    std::optional<TaskID>           getCreatedTaskID();
    bool                            getSuccessStatus();
    std::optional<std::string>      getErrorMessage();

private:

    TaskCreationResult( const std::optional<TaskID> &created_id,
                        bool success,
                        const std::optional<std::string>& error_message) :
    created_id_(created_id),
    success_(success),
    error_message_(error_message)
    {}

private:
    std::optional<TaskID>           created_id_;

    bool                            success_;
    std::optional<std::string>      error_message_;
};


#endif //TODOLIST_TASKCREATIONRESULT_H
