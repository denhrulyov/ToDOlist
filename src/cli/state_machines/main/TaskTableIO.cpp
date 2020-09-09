//
// Created by denis on 20.08.20.
//

#include "TaskTableIO.h"
#include "ConsoleContextInterface.h"

void task_table_io::print(ConsoleContextInterface& context) {
    TaskNumber i = 1;
    auto map_iter = context.getMatchingTablePositionToID().begin();
    while (map_iter != context.getMatchingTablePositionToID().end()) {
        if (i == map_iter->first) {
            context.getIO().putLine(std::to_string(map_iter->first));
            ++map_iter;
        }
        ++i;
    }
}