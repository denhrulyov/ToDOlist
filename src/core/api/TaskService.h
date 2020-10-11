//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "core/RepositoryHolder.h"
#include "TaskServiceInterface.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

/*
 * Public api for manipulating tasks.
 *
 * @author Denys Hrulov
 */
class TaskService : public TaskServiceInterface {

public:
    explicit TaskService(std::unique_ptr<RepositoryHolder> model_holder)
    :
    model_holder_(std::move(model_holder))
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
    ~TaskService() override =                               default;

private:
    std::unique_ptr<RepositoryHolder>                   model_holder_;
};


bool validate_date(const BoostDate& date);

#endif //EVAL_TASKSERVICE_H
