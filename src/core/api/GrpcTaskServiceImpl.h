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

private:
    std::unique_ptr<RepositoryHolder> repository_holder_;
};


void ConvertTogRPC(TaskCreationResult& repos_result, AddTaskResponse* response);

#endif //TODOLIST_GRPCTASKSERVICEIMPL_H
