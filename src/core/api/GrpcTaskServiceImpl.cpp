//
// Created by denis on 22.10.20.
//

#include "GrpcTaskServiceImpl.h"

void ConvertTogRPC(TaskCreationResult& repos_result, AddTaskResponse* response) {
    bool status =       repos_result.getSuccessStatus();
    auto error_msg =    repos_result.getErrorMessage();
    auto id =           repos_result.getCreatedTaskID();
    response->set_success(status);
    if (error_msg) {
        response->set_error_msg(error_msg.value());
    }
    if (id) {
        auto id_msg = std::make_unique<TaskIdMessage>();
        id_msg->set_id(id.value().getInt());
        response->set_allocated_created_id(id_msg.release());
    }
}


GrpcTaskServiceImpl::GrpcTaskServiceImpl(std::unique_ptr<RepositoryHolder>&& repos_holder)
:
repository_holder_(std::move(repos_holder))
{}

Status
GrpcTaskServiceImpl::GetTaskByID(ServerContext* context, const TaskIdMessage* request, GetTaskByIDResponse* response) {
    auto repos_result = repository_holder_->GetRepository().getTaskData(TaskID(request->id()));
    if (repos_result) {
        if (!proto_convert::WriteToMessage(repos_result.value(), response->mutable_task())) {
            response->set_allocated_task(nullptr);
        }
    }
    return Status::OK;
}
Status
GrpcTaskServiceImpl::AddTask(ServerContext* context, const TaskData* request, AddTaskResponse* response) {
    if (!validate_date(proto_convert::RestoreDate(request->date()))) {
        response->set_success(false);
        response->set_error_msg("Task date is out of allowed range");
        return Status::OK;
    }
    TaskCreationResult result =
            repository_holder_
                    ->GetRepository()
                    .addTask(proto_convert::RestoreFromMessage(*request));
    ConvertTogRPC(result, response);
    return Status::OK;
}
Status
GrpcTaskServiceImpl::AddSubTask(ServerContext* context, const AddSubTaskRequest* request, AddTaskResponse* response) {
    if (!validate_date(proto_convert::RestoreDate(request->task().date()))) {
        response->set_success(false);
        response->set_error_msg("Task date is out of allowed range");
        return Status::OK;
    }
    TaskCreationResult result =
            repository_holder_
                    ->GetRepository()
                    .addSubTask(
                            TaskID(request->parent().id()),
                            proto_convert::RestoreFromMessage(request->task()));
    ConvertTogRPC(result, response);
    return Status::OK;
}

