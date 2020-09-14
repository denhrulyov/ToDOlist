//
// Created by denis on 20.08.20.
//

#include "TaskTableIO.h"
#include "ConsoleContextInterface.h"


void task_table_io::print(ConsoleContextInterface& context) {
    TaskNumber i = 1;
    auto& service = context.getTaskService();
    auto map_iter = context.getMatchingTablePositionToID().begin();
    while (map_iter != context.getMatchingTablePositionToID().end()) {
        auto [number, id] = *map_iter;
        if (i == number) {
            std::string row_out = std::to_string(map_iter->first) + ".) ";
            std::optional<TaskDTO> dto = service.getTaskByID(id);
            if (dto) {
                row_out += dto->getName() + " " + boost::gregorian::to_simple_string(dto->getDate());
            } else {
                row_out += "## deleted ##";
            }
            context.getIO().putLine(row_out);
            ++map_iter;
        }
        ++i;
    }
}