//
// Created by denis on 15.09.20.
//

#ifndef TODOLIST_CLITASKIO_H
#define TODOLIST_CLITASKIO_H

#include "ConsoleIOInterface.h"
#include "cli/state_machines/main/states/utils/Utils.h"

namespace cli_task_io {
    void print(ConsoleIOInterface& io, const TaskDTO& dto);
    void print_brief(ConsoleIOInterface& io, const TaskDTO& dto);
}

#endif //TODOLIST_CLITASKIO_H
