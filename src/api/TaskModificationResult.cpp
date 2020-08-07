//
// Created by denis on 06.08.20.
//

#include "TaskModificationResult.h"

TaskModificationResult TaskModificationResult::success(const TaskID &id_modified) {
    return TaskModificationResult(std::make_optional(id_modified), false, std::nullopt);
}

std::optional<TaskID> TaskModificationResult::getModifiedTaskID() {
    return modified_id_;
}

TaskModificationResult::TaskModificationResult(const std::optional<TaskID> &modified_id, bool success,
                                               const std::optional<std::string> &error_message) :
                                               RequestResult(success, error_message),
                                               modified_id_(modified_id)
                                               {}

TaskModificationResult TaskModificationResult::taskNotFound() {
    return TaskModificationResult(std::nullopt, false, "Task not found");
}

TaskModificationResult TaskModificationResult::error(const std::string &message) {
    return TaskModificationResult(std::nullopt, false, message);
}
