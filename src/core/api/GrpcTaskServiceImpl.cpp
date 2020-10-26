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

void ConvertTogRPC(const std::vector<RepositoryTaskDTO>& tasks, TaskDTOList* response) {
    for (const auto& task : tasks) {
        GrpcTaskDTO* grpc_dto = response->add_tasks();
        auto id =         std::make_unique<TaskIdMessage>();
        auto grpc_task =  std::make_unique<TaskData>();
        id->set_id(task.getId());
        grpc_dto->set_allocated_id(id.release());
        grpc_dto->set_allocated_task(grpc_task.release());
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

Status
GrpcTaskServiceImpl::GetAllWithLabel(ServerContext *context, const StringRequest *request, TaskDTOList *response) {
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                ->GetRepository()
                .getWithLabel(request->str());
    ConvertTogRPC(result_set, response);
    return Status::OK;
}

grpc::Status GrpcTaskServiceImpl::GetToday(ServerContext *context, const EmptyRequest *request, TaskDTOList *response) {
    using boost::gregorian::day_clock;
    using boost::gregorian::days;
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                    ->GetRepository()
                    .getToDate(day_clock::local_day());
    ConvertTogRPC(result_set, response);
    return Status::OK;
}

Status
GrpcTaskServiceImpl::GetThisWeek(ServerContext *context, const EmptyRequest *request, TaskDTOList *response) {
    using boost::gregorian::day_clock;
    using boost::gregorian::days;
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                    ->GetRepository()
                    .getToDate(day_clock::local_day() + days(6));
    ConvertTogRPC(result_set, response);
    return Status::OK;
}

Status
GrpcTaskServiceImpl::GetAllTasks(ServerContext *context, const EmptyRequest *request, TaskDTOList *response) {
    using boost::gregorian::day_clock;
    using boost::gregorian::days;
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                    ->GetRepository()
                    .getToDate(service::max_date);
    ConvertTogRPC(result_set, response);
    return Status::OK;
}

Status
GrpcTaskServiceImpl::GetSubTasks(ServerContext *context, const TaskIdMessage *request, TaskDTOList *response) {
    using boost::gregorian::day_clock;
    using boost::gregorian::days;
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                    ->GetRepository()
                    .getSubTasks(TaskID(request->id()));
    ConvertTogRPC(result_set, response);
    return Status::OK;
}

Status
GrpcTaskServiceImpl::GetSubTasksRecursive(ServerContext *context, const TaskIdMessage *request, TaskDTOList *response) {
    using boost::gregorian::day_clock;
    using boost::gregorian::days;
    std::vector<RepositoryTaskDTO> result_set =
            repository_holder_
                    ->GetRepository()
                    .getSubTasksRecursive(TaskID(request->id()));
    ConvertTogRPC(result_set, response);
    return Status::OK;;
}
