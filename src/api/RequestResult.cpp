//
// Created by denis on 06.08.20.
//

#include "RequestResult.h"

bool RequestResult::getSuccessStatus() {
    return success_;
}

std::optional<std::string> RequestResult::getErrorMessage() {
    return error_message_;
}

RequestResult::RequestResult(bool success, const std::optional<std::string>& error_message) :
success_(success), error_message_(error_message)
{}
