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
#include <core/RepositoryHolder.h>
#include <core/persistence/ProtoConvert.h>
#include "TaskService.grpc.pb.h"
#include "TaskService.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

namespace grpc_task_service {

class GrpcTaskServiceImpl final : public GrpcTaskService::Service {

public:
    explicit  GrpcTaskServiceImpl(std::unique_ptr<RepositoryHolder>&& repos_holder);

    /*
     * Gives task with given id if such exists in system.
     *
     * @param server context - additional server info
     * @param request containing task id.
     * @param response task DTO if such task exists otherwise nullopt.
     *
     * @return server status
     */
    Status    GetTaskByID(ServerContext* context, const TaskIdMessage* request, GetTaskByIDResponse* response) override;
    /*
    * Adds single task to system. It will not belong to any other task.
    *
    *
    * @param server context - additional server info
    * @param request containing DTO representing the task. ID will be ignored.
    * @param response object containing id of new created task or info about possible errors.
    *
    * @return server status
    */
    Status    AddTask(ServerContext* context, const TaskData* request, AddTaskResponse* response) override;
    /*
     * Adds single task to system. It will belong to task with specified id.
     *
     * @param server context - additional server info
     * @param request containing id of task, which will include the given as subtask
     * and DTO representing the task. ID will be ignored.
     * @param response object containing id of new created task or info about possible errors occurred.
     *
     * @return server status
     */
    Status    AddSubTask(ServerContext* context, const AddSubTaskRequest* request, AddTaskResponse* response) override;
    /*
     * Gives all tasks with given label already sorted by priority.
     *
     * @param server context - additional server info
     * @param request containing task label
     * @param response containing list of tasks
     *
     * @return server status
     */
    Status    GetAllWithLabel(ServerContext* context, const StringMessage* request, TaskDTOList* response) override;
    /*
    * Gives tasks for today already sorted by priority
    *
    * @param server context - additional server info
    * @param empty request
    * @param response containing list of tasks.
    *
    * @return server status
    */
    Status    GetToday(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    /*
     * Gives tasks for this week already sorted by priority
     *
     * @param server context - additional server info
     * @param empty request
     * @param response containing list of tasks
     *
     * @return server status
     */
    Status    GetThisWeek(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    /*
     * Gives all tasks already sorted by priority.
     *
     * @param server context - additional server info
     * @param empty request
     * @param response containing list of tasks
     *
     * @return server status
     */
    Status    GetAllTasks(ServerContext* context, const EmptyRequest* request, TaskDTOList* response) override;
    /*
     * Gives all direct subtasks of task.
     *
     * @param server context - additional server info
     * @param request containing task id.
     * @param response containing list of tasks
     *
     * @return server status
     */
    Status    GetSubTasks(ServerContext* context, const TaskIdMessage* request, TaskDTOList* response) override;
    /*
     * Gives all subtasks, subtasks of subtasks and so on recursively.
     *
     * @param server context - additional server info
     * @param request containing task id.
     * @param response containing list of tasks.
     *
     * @return server status
     */
    Status    GetSubTasksRecursive(ServerContext* context, const TaskIdMessage* request, TaskDTOList* response) override;
    /*
    * Deletes task from system. All subtasks will be deleted recursively.
    *
    * @param server context - additional server info
    * @param request containing id of task to delete.
    * @param response object containing id of new created task or info about possible error occurred.
    *
    * @return server status
    */
    Status    DeleteTask(ServerContext* context, const TaskIdMessage* request, DefaultResponse* response) override;
    /*
     * Postpones the task, changing its date to given.
     *
     * @param server context - additional server info
     * @param request containing id of task to postpone and new date to assign task
     * @param response object containing id of modified task or info about possible error occurred
     *
     * @return server status
     */
    Status    PostponeTask(ServerContext* context, const PostponeRequest* request, DefaultResponse* response) override;
    /*
     * Marks task as completed. All subtasks will be deleted recursively.
     *
     * @param server context - additional server info
     * @param request containing id of task to delete.
     * @param response object info about success or possible error occurred
     *
     * @return server status
     */
    Status    CompleteTask(ServerContext* context, const TaskIdMessage* request, DefaultResponse* response) override;
    /*
     * Saves program state to file
     *
     * @param server context - additional server info
     * @param request containing filepath
     * @param response object containing info about success or error
     *
     * @return server status
     */
    Status    SaveToFile(ServerContext* context, const StringMessage* request, DefaultResponse* response) override;
    /*
    * Loads program state from file
    *
    * @param server context - additional server info
    * @param request containing filepath
    * @param response object containing info about success or error
    *
    * @return server status
    */
    Status    LoadFromFile(ServerContext* context, const StringMessage* request, DefaultResponse* response) override;

private:
    std::unique_ptr<RepositoryHolder> repository_holder_;
};

const BoostDate max_date(
            BoostDate::year_type(3000),
            BoostDate::month_type(1),
            BoostDate::day_type(1));

/*
 * Converts result given by repository to gRPC response
 *
 * @param source : result object given by repository
 * @param destination : gRPC response
 */
template<class ReposResult>
void ConvertTogRPC(ReposResult& repos_result, DefaultResponse* response);
/*
 * Converts result given by repository to gRPC response
 *
 * @param source : result object given by repository
 * @param destination : gRPC response
 */
void ConvertTogRPC(TaskCreationResult& repos_result, AddTaskResponse* response);
/*
 * Converts task list given by repository to gRPC analogue
 *
 * @param source : vector of Repository tasks
 * @param destination : gRPC response containing converted tasks
 */
void ConvertTogRPC(const std::vector<RepositoryTaskDTO>& tasks, TaskDTOList* response);
/*
 * Checks if date is within required boundaries
 *
 * @param date to check
 */
bool validate_date(const BoostDate& date);

}

#endif //TODOLIST_GRPCTASKSERVICEIMPL_H
