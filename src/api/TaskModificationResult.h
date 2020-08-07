//
// Created by denis on 06.08.20.
//

#ifndef TODOLIST_TASKMODIFICATIONRESULT_H
#define TODOLIST_TASKMODIFICATIONRESULT_H

#include "RequestResult.h"

class TaskModificationResult : public RequestResult {

public:
    TaskModificationResult( const std::optional<TaskID>& modified_id,
                            bool success,
                            const std::optional<std::string>& error_message);

public:
    static TaskModificationResult success(const TaskID &id_modified);
    static TaskModificationResult taskNotFound();
    static TaskModificationResult error(const std::string& message);

public:
    std::optional<TaskID>           getModifiedTaskID();


private:
    std::optional<TaskID>           modified_id_;

};


#endif //TODOLIST_TASKMODIFICATIONRESULT_H
