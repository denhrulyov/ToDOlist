//
// Created by denis on 27.10.20.
//

#ifndef TODOLIST_GRPCTASKSERVICEADAPTOR_H
#define TODOLIST_GRPCTASKSERVICEADAPTOR_H

#include "core/persistence/ProtoConvert.h"
#include "TaskServiceInterface.h"
#include "TaskService.grpc.pb.h"
#include "TaskService.pb.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class GrpcTaskServiceAdaptor : public TaskServiceInterface {
public:
    explicit GrpcTaskServiceAdaptor(std::unique_ptr<GrpcTaskService::Stub> stub)
    :
    stub_(std::move(stub))
    {}

public:
    std::vector<TaskDTO>                                    getToday() override;
    std::vector<TaskDTO>                                    getThisWeek() override;
    std::vector<TaskDTO>                                    getAllTasks() override;
    std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label) override;
    std::optional<TaskDTO>                                  getTaskByID(TaskID id) override;
    std::vector<TaskDTO>                                    getSubTasks(TaskID id) override;
    std::vector<TaskDTO>                                    getSubTasksRecursive(TaskID id) override;

public:
    TaskCreationResult                                      addTask(const TaskDTO &task_data) override;
    TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &task_data) override;
    TaskModificationResult                                  deleteTask(TaskID id) override;
    TaskModificationResult                                  postponeTask(TaskID id, BoostDate) override;
    RequestResult                                           complete(TaskID id) override;

public:
    RequestResult                                           saveToFile(const std::string& filepath) override;
    RequestResult                                           loadFromFile(const std::string& filepath) override;

public:
    ~GrpcTaskServiceAdaptor() override =                    default;

private:
    std::unique_ptr<GrpcTaskService::Stub>                  stub_;
};

std::vector<TaskDTO>    RestoreFromGrpcDTOList(const TaskDTOList& all);
TaskDTO                 RestoreFromGrpcDTO(const GrpcTaskDTO& all);
template<class Result>
Result                  RestoreResult(const DefaultResponse& response);
TaskCreationResult      RestoreResult(const AddTaskResponse& response);


/**************************************************************************************************************/

template<class Result>
Result RestoreResult(const DefaultResponse& response) {
    bool status =         response.success();
    auto error_msg =      status ? std::nullopt : std::make_optional(response.error_msg());
    return Result(status, error_msg);
}


#endif //TODOLIST_GRPCTASKSERVICEADAPTOR_H
