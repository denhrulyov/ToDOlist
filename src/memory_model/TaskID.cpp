//
// Created by denis on 19.07.20.
//

#include "TaskID.h"

TaskID TaskIDFactory::getNextAvailableID() {
    return TaskID(current_id_++);
}
