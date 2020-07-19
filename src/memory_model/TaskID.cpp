//
// Created by denis on 19.07.20.
//

#include "TaskID.h"

const unsigned int TaskID::id_invalid_ = std::numeric_limits<unsigned int>::max();

TaskID TaskIDFactory::generateID() {
    return TaskID(current_id_++);
}


