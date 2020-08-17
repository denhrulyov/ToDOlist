//
// Created by denis on 06.08.20.
//

#include "TaskModificationResult.h"

TaskModificationResult TaskModificationResult::success() {
    return TaskModificationResult(true, std::nullopt);
}


TaskModificationResult::TaskModificationResult(bool success,
                                               const std::optional<std::string> &error_message) :
                                               RequestResult(success, error_message)
                                               {}

TaskModificationResult TaskModificationResult::taskNotFound() {
    return TaskModificationResult(false, "Task not found");
}

TaskModificationResult TaskModificationResult::error(const std::string &message) {
    return TaskModificationResult(false, message);
}
