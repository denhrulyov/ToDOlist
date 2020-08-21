//
// Created by denis on 20.08.20.
//

#include "TaskTableIO.h"
#include "ConsoleContext.h"

void task_table_io::print(ConsoleContext& context) {
    TaskNumber i = 1;
    auto map_iter = context.getTaskTable().begin();
    while (map_iter != context.getTaskTable().end()) {
        if (i == map_iter->first) {
            context.getIO().log(std::to_string(map_iter->first));
            ++map_iter;
        }
        ++i;
    }
}