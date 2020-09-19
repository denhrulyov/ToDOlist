//
// Created by denis on 18.08.20.
//

#include "ConsoleContext.h"
#include "cli/state_machines/main/states/State.h"

ConsoleContext::ConsoleContext(
    std::unique_ptr<TaskServiceInterface> service,
    std::unique_ptr<ConsoleIOInterface> io,
    std::unique_ptr<OstreamServiceSerializer> serializer,
    std::unique_ptr<IstreamServiceDeserializer> deserializer)
:
service_(std::move(service)),
io_(std::move(io)),
serializer_(std::move(serializer)),
deserializer_(std::move(deserializer)),
task_buffer_(std::nullopt)
{}


void ConsoleContext::setTaskService(std::unique_ptr<TaskServiceInterface> service) {
    service_ = std::move(service);
}


std::optional<TaskDTO> ConsoleContext::getTaskBuffer() {
    return task_buffer_;
}

TaskServiceInterface &ConsoleContext::getTaskService() {
    return *service_;
}

ConsoleIOInterface & ConsoleContext::getIO() {
    return *io_;
}

std::map<TaskNumber, TaskID> &ConsoleContext::getMatchingTablePositionToID() {
    return task_table_;
}

std::map<TaskID, TaskNumber> &ConsoleContext::getMatchingIDtoTablePosition() {
    return id_table_;
}

std::optional<TaskID> ConsoleContext::getBufferedId() const {
    return id_buffer_;
}

void ConsoleContext::fillTaskBuffer(const TaskDTO& dto) {
    task_buffer_ = dto;
}

void ConsoleContext::fillIDBuffer(TaskID id) {
    id_buffer_ = id;
}

void ConsoleContext::fillTable(const std::vector<TaskDTO> &tasks) {
    task_table_.clear();
    TaskNumber i = 1;
    for (const TaskDTO& dto : tasks) {
        task_table_[i] = dto.getId();
        ++i;
    }
}

OstreamServiceSerializer &ConsoleContext::getSerializer() {
    return *serializer_;
}

IstreamServiceDeserializer &ConsoleContext::getDeserializer() {
    return *deserializer_;
}



