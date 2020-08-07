//
// Created by denis on 28.07.20.
//

#ifndef TODOLIST_TASKCREATIONRESULT_H
#define TODOLIST_TASKCREATIONRESULT_H

#include "RequestResult.h"
#include "memory_model/TaskID.h"

class TaskCreationResult : public RequestResult {

public:
    static TaskCreationResult       success(const TaskID &id_created);
    static TaskCreationResult       error(const std::string& message);
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
