//
// Created by denis on 22.10.20.
//

#ifndef TODOLIST_GRPCTASKSERVICEIMPL_H
#define TODOLIST_GRPCTASKSERVICEIMPL_H


#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <core/api/TaskService.h>
#include <core/RepositoryHolder.h>
#include <core/persistence/ProtoConvert.h>
#include "TaskService.grpc.pb.h"
#include "TaskService.pb.h"



using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


class GrpcTaskServiceImpl final : public GrpcTaskService::Service {

public:
    explicit  GrpcTaskServiceImpl(std::unique_ptr<RepositoryHolder>&& repos_holder);
    Status    GetTaskByID(ServerContext* context, const TaskIdMessage* request, GetTaskByIDResponse* response) override;
    Status    AddTask(ServerContext* context, const TaskData* request, AddTaskResponse* response) override;
    Status    AddSubTask(ServerContext* context, const AddSubTaskRequest* request, AddTaskResponse* response) override;
    Status    GetAllWithLabel(ServerContext* context, const StringRequest* request, TaskDTOList* response) override;
    Status    GetToday(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    Status    GetThisWeek(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    Status    GetAllTasks(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    Status    GetSubTasks(ServerContext* context, const TaskIdMessage* request, TaskDTOList* response) override;
    Status    GetSubTasksRecursive(ServerContext* context, const TaskIdMessage* request, TaskDTOList* response) override;
    Status    DeleteTask(ServerContext* context, const TaskIdMessage* request, DefaultResponse* response) override;
    Status    PostponeTask(ServerContext* context, const PostponeRequest* request, DefaultResponse* response) override;
    Status    CompleteTask(ServerContext* context, const TaskIdMessage* request, DefaultResponse* response) override;
    Status    SaveToFile(ServerContext* context, const StringRequest* request,DefaultResponse* response) override;
    Status    LoadFromFile(ServerContext* context, const StringRequest* request,DefaultResponse* response) override;

private:
    std::unique_ptr<RepositoryHolder> repository_holder_;
};

template<class ReposResult>
void ConvertTogRPC(ReposResult& repos_result, DefaultResponse* response);
void ConvertTogRPC(TaskCreationResult& repos_result, AddTaskResponse* response);
void ConvertTogRPC(const std::vector<RepositoryTaskDTO>& tasks, TaskDTOList* response);

#endif //TODOLIST_GRPCTASKSERVICEIMPL_H
