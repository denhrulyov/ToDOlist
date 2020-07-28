//
// Created by denis on 28.07.20.
//

#include "TaskIDFactory.h"

TaskID TaskIDFactory::generateID() {
    return TaskID(current_id_++);
}
