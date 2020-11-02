//
// Created by denis on 27.10.20.
//

#include "GrpcTaskServiceAdaptor.h"


TaskDTO RestoreFromGrpcDTO(const GrpcTaskDTO& dto) {
    return TaskDTO::create(
            TaskID(dto.id().id()),
            dto.task().name(),
            proto_convert::RestorePriority(dto.task().prior()),
            dto.task().label(),
            proto_convert::RestoreDate(dto.task().date()),
            dto.task().completed()
            );
}

std::vector<TaskDTO> RestoreFromGrpcDTOList(const TaskDTOList& task) {
    std::vector<TaskDTO> converted;
    std::transform(
            task.tasks().begin(), task.tasks().end(),
            std::back_inserter(converted),
            [] (const GrpcTaskDTO& grpc_dto) -> TaskDTO {
                return RestoreFromGrpcDTO(grpc_dto);
            });
    return converted;
}


TaskCreationResult RestoreResult(const AddTaskResponse& response) {
    bool status =         response.success();
    auto error_msg =      status ? std::nullopt : std::make_optional(response.error_msg());
    return TaskCreationResult(
            TaskID(response.created_id().id()),
            status,
            error_msg);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getToday() {
    EmptyRequest request;
    TaskDTOList response;
    ClientContext client_context;
    stub_->GetToday(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getThisWeek() {
    EmptyRequest request;
    TaskDTOList response;
    ClientContext client_context;
    stub_->GetThisWeek(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getAllTasks() {
    EmptyRequest request;
    TaskDTOList response;
    ClientContext client_context;

    stub_->GetAllTasks(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getAllWithLabel(const std::string &label) {
    StringMessage request;
    TaskDTOList response;
    ClientContext client_context;

    request.set_str(label);
    stub_->GetAllWithLabel(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

std::optional<TaskDTO> GrpcTaskServiceAdaptor::getTaskByID(TaskID id) {
    auto request = std::make_unique<TaskIdMessage>();
    auto response = std::make_unique<GetTaskByIDResponse>();
    ClientContext client_context;

    request->set_id(id);
    stub_->GetTaskByID(&client_context, *request, response.get());
    if (!response->has_task()) {
        return std::nullopt;
    }

    GrpcTaskDTO resulting_dto;
    resulting_dto.set_allocated_id(request.release());
    resulting_dto.set_allocated_task(response->release_task());
    return RestoreFromGrpcDTO(resulting_dto);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getSubTasks(TaskID id) {
    TaskIdMessage request;
    TaskDTOList response;
    ClientContext client_context;

    request.set_id(id);
    stub_->GetSubTasks(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

std::vector<TaskDTO> GrpcTaskServiceAdaptor::getSubTasksRecursive(TaskID id) {
    TaskIdMessage request;
    TaskDTOList response;
    ClientContext client_context;

    request.set_id(id);
    stub_->GetSubTasksRecursive(&client_context, request, &response);
    return RestoreFromGrpcDTOList(response);
}

TaskCreationResult GrpcTaskServiceAdaptor::addTask(const TaskDTO &task_data) {
    TaskData request;
    AddTaskResponse response;
    ClientContext client_context;

    proto_convert::WriteToMessage(task_data, &request);
    stub_->AddTask(&client_context, request, &response);
    return RestoreResult(response);
}

TaskCreationResult GrpcTaskServiceAdaptor::addSubTask(TaskID parent, const TaskDTO &task_data) {
    AddSubTaskRequest request;
    AddTaskResponse response;
    ClientContext client_context;

    request.set_allocated_parent(new TaskIdMessage);
    request.set_allocated_task(new TaskData);

    request.mutable_parent()->set_id(parent);
    proto_convert::WriteToMessage(task_data, request.mutable_task());

    stub_->AddSubTask(&client_context, request, &response);
    return RestoreResult(response);
}

TaskModificationResult GrpcTaskServiceAdaptor::deleteTask(TaskID id) {
    TaskIdMessage request;
    DefaultResponse response;
    ClientContext client_context;

    request.set_id(id);
    stub_->DeleteTask(&client_context, request, &response);
    return RestoreResult<TaskModificationResult>(response);
}

TaskModificationResult GrpcTaskServiceAdaptor::postponeTask(TaskID id, BoostDate date_postpone) {
    PostponeRequest request;
    DefaultResponse response;
    ClientContext client_context;

    request.set_allocated_id(new TaskIdMessage);
    request.mutable_id()->set_id(id);
    request.set_allocated_date_postpone(
            proto_convert::GetProtobufDate(date_postpone).release());

    stub_->PostponeTask(&client_context, request, &response);
    return RestoreResult<TaskModificationResult>(response);
}

RequestResult GrpcTaskServiceAdaptor::complete(TaskID id) {
    TaskIdMessage request;
    DefaultResponse response;
    ClientContext client_context;

    request.set_id(id);
    stub_->CompleteTask(&client_context, request, &response);
    return RestoreResult<TaskModificationResult>(response);
}

RequestResult GrpcTaskServiceAdaptor::saveToFile(const std::string &filepath) {
    StringMessage request;
    DefaultResponse response;
    ClientContext client_context;

    request.set_str(filepath);
    stub_->SaveToFile(&client_context, request, &response);
    return RestoreResult<RequestResult>(response);
}

RequestResult GrpcTaskServiceAdaptor::loadFromFile(const std::string &filepath) {
    StringMessage request;
    DefaultResponse response;
    ClientContext client_context;

    request.set_str(filepath);
    stub_->LoadFromFile(&client_context, request, &response);
    return RestoreResult<RequestResult>(response);
}
