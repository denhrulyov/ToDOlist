//
// Created by denis on 22.10.20.
//

#include "GrpcTaskServiceImpl.h"
using namespace grpc_task_service;

bool grpc_task_service::validate_date(const BoostDate& date) {
    return  date <= grpc_task_service::max_date &&
            date >= boost::gregorian::day_clock::local_day();
}

void grpc_task_service::ConvertTogRPC(TaskCreationResult& repos_result, AddTaskResponse* response) {
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

template<class ReposResult>
void grpc_task_service::ConvertTogRPC(ReposResult& repos_result, DefaultResponse* response) {
    bool status =       repos_result.getSuccessStatus();
    auto error_msg =    repos_result.getErrorMessage();
    response->set_success(status);
    if (error_msg) {
        response->set_error_msg(error_msg.value());
    }
}

void grpc_task_service::ConvertTogRPC(const std::vector<RepositoryTaskDTO>& tasks, TaskDTOList* response) {
    for (auto& task : tasks) {
        auto id =         std::make_unique<TaskIdMessage>();
        auto grpc_task =  std::make_unique<TaskData>();
        proto_convert::WriteToMessage(task, grpc_task.get());
        id->set_id(task.getId());

        GrpcTaskDTO* grpc_dto = response->add_tasks();
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
GrpcTaskServiceImpl::GetAllWithLabel(ServerContext *context, const StringMessage *request, TaskDTOList *response) {
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
                    .getToDate(max_date);
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

Status GrpcTaskServiceImpl::DeleteTask(ServerContext *context, const TaskIdMessage *request, DefaultResponse *response) {
    TaskModificationResult result =
            repository_holder_
                ->GetRepository()
                .dropTask(TaskID(request->id()));
    ConvertTogRPC(result, response);
    return Status::OK;
}

Status GrpcTaskServiceImpl::PostponeTask(ServerContext *context, const PostponeRequest *request, DefaultResponse *response) {
    auto id = TaskID(request->id().id());
    // Getting requested task current data
    std::optional<RepositoryTaskDTO> old_task_opt =
            repository_holder_
                ->GetRepository()
                .getTaskData(id);
    if (!old_task_opt) {
        auto not_found_res = TaskModificationResult::taskNotFound();
        ConvertTogRPC(not_found_res, response);
        return Status::OK;
    }

    // Creating the same task but with modified date
    RepositoryTaskDTO old_task = old_task_opt.value();
    RepositoryTaskDTO postponed_task = RepositoryTaskDTO::create(
            id,
            old_task.getName(),
            old_task.getPriority(),
            old_task.getLabel(),
            proto_convert::RestoreDate(request->date_postpone()),
            old_task.isCompleted()
    );

    TaskModificationResult result =
            repository_holder_->GetRepository().setTaskData(
                    id,
                    postponed_task
            );
    ConvertTogRPC(result, response);
    return Status::OK;
}

Status GrpcTaskServiceImpl::CompleteTask(ServerContext *context, const TaskIdMessage *request, DefaultResponse *response) {
    auto id = TaskID(request->id());
    TaskRepositoryInterface& model = repository_holder_->GetRepository();
    auto root_complete_result = model.setCompleted(id);
    if (!root_complete_result.getSuccessStatus()) {
        ConvertTogRPC(root_complete_result, response);
        return Status::OK;
    }
    for (const auto& task : model.getSubTasksRecursive(id)) {
        auto complete_result = model.setCompleted(task.getId());
        if (!complete_result.getSuccessStatus()) {
            ConvertTogRPC(complete_result, response);
            return Status::OK;
        }
    }
    auto res_success = RequestResult::success();
    ConvertTogRPC(res_success, response);
    return Status::OK;
}

Status GrpcTaskServiceImpl::SaveToFile(ServerContext *context, const StringMessage *request, DefaultResponse *response) {
    bool saved = repository_holder_->SaveRepositoryToFile(request->str());
    auto result = saved ? RequestResult::success() : RequestResult(false, "Could not save");
    ConvertTogRPC(result, response);
    return Status::OK;
}

Status GrpcTaskServiceImpl::LoadFromFile(ServerContext *context, const StringMessage *request, DefaultResponse *response) {
    bool loaded = repository_holder_->LoadRepositoryFromFile(request->str());
    auto result = loaded ? RequestResult::success() : RequestResult(false, "Could not load");
    ConvertTogRPC(result, response);
    return Status::OK;
}
