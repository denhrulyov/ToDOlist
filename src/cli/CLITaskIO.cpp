//
// Created by denis on 15.09.20.
//

#include "CLITaskIO.h"

void cli_task_io::print(ConsoleIOInterface& io, const TaskDTO& dto) {
    io.putLine(std::string("name :     ")
               + field_repr(dto.getName()));
    io.putLine(std::string("priority : ")
               + field_repr(dto.getPriority()));
    io.putLine(std::string("label :    ")
               + field_repr(dto.getLabel()));
    io.putLine(std::string("date :     ")
               + field_repr(std::optional(dto.getDate())));
    io.putLine(std::string("Completed? : ")
               + (dto.isCompleted() ? "YES" : "NO"));
}

void cli_task_io::print_brief(ConsoleIOInterface& io, const TaskDTO& dto) {
    std::string row_out =
                dto.getName() + " "
               + boost::gregorian::to_simple_string(dto.getDate())
               + (dto.isCompleted() ? "(COMPLETED)" : "");
    io.putLine(row_out);
}