//
// Created by denis on 20.07.20.
//

#include "UserTaskID.h"

std::vector<std::size_t> UserTaskID::getLevelIndices() {
    return level_index_;
}

UserTaskID UserTaskID::getMainTaskID() {
    if (level_index_.empty()) {
        return *this;
    }
    auto index_path = std::vector(level_index_.begin(), level_index_.end() - 1);
    return UserTaskID(index_path);
}
