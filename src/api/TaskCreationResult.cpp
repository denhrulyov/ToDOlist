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

bool TaskCreationResult::getSuccessStatus() {
    return success_;
}

std::optional<TaskID> TaskCreationResult::getCreatedTaskID() {
    return created_id_;
}

std::optional<std::string> TaskCreationResult::getErrorMessage() {
    return error_message_;
}
