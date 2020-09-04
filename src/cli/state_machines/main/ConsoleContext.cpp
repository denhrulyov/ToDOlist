//
// Created by denis on 18.08.20.
//

#include "ConsoleContext.h"
#include "cli/state_machines/main/states/State.h"

ConsoleContext::ConsoleContext(
    std::unique_ptr<TaskServiceInterface> service,
    std::unique_ptr<ConsoleIOInterface> io)
:
service_(std::move(service)),
io_(std::move(io))
{}


std::optional<TaskDTO> ConsoleContext::getTaskBuffer() {
    return task_buffer_.value();
}

TaskServiceInterface &ConsoleContext::getTaskService() {
    return *service_;
}

ConsoleIOInterface & ConsoleContext::getIO() {
    return *io_;
}

std::map<TaskNumber, TaskID> &ConsoleContext::getTaskTable() {
    return task_table_;
}

std::map<TaskID, TaskNumber> &ConsoleContext::getIDTable() {
    return id_table_;
}

std::optional<TaskID> ConsoleContext::getBufferedId() const {
    return id_buffer_;
}

void ConsoleContext::fillTaskBuffer(const TaskDTO& dto) {
    task_buffer_ = dto;
}







