//
// Created by denis on 21.08.20.
//

#include "Utils.h"


std::string field_repr(const std::optional<TaskPriority>& field) {
    std::string result;
    std::stringstream ss;
    if (field.has_value()) {
        ss << console_task_io::priorty_repr.at(field.value());
    } else {
        ss << "### unknown ###";
    }
    ss >> result;
    return result;
}
