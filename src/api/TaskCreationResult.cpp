//
// Created by denis on 28.07.20.
//

#include "TaskCreationResult.h"

TaskCreationResult TaskCreationResult:: success(const TaskID &id_created) {
    return TaskCreationResult(std::make_optional(id_created), true, std::nullopt);
}
TaskCreationResult TaskCreationResult::taskNotFound() {
    return TaskCreationResult(std::nullopt, false, "Task not found");
}

TaskCreationResult TaskCreationResult::error(const std::string &message) {
    return TaskCreationResult(std::nullopt, false, message);
}


std::optional<TaskID> TaskCreationResult::getCreatedTaskID() {
    return created_id_;
}

TaskCreationResult::TaskCreationResult(const std::optional<TaskID> &created_id, bool success,
                                       const std::optional<std::string> &error_message) :
        RequestResult(success, error_message),
        created_id_(created_id)
        {}


