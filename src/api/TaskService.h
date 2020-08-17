//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/structure/TaskNode.h"
#include "memory_model/data/TaskStorageInterface.h"
#include "TaskCreationResult.h"
#include "memory_model/data/TaskIDFactory.h"
#include "memory_model/structure/LinkManager.h"
#include "utils/data_transfer/TaskDTOConverter.h"
#include "TaskModificationResult.h"
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
    TaskService(
            std::unique_ptr<TaskStorageInterface>                   storage,
            std::unique_ptr<PriorityViewInterface<BoostDate>>       view_time,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label,
            std::unique_ptr<LinkManagerInterface>                   link_manger)
    :
    storage_(std::move(storage)),
    by_time_(std::move(view_time)),
    by_label_(std::move(view_label)),
    link_manager_(std::move(link_manger))
    {}

public:
    std::vector<TaskDTO>                                    getToday();
    std::vector<TaskDTO>                                    getThisWeek();
    std::vector<TaskDTO>                                    getAllTasks();
    std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label);
    std::optional<TaskDTO>                                  getTaskByID(TaskID id);

public:
    TaskCreationResult                                      addTask(const TaskDTO &task_data);
    TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &task_data);
    TaskModificationResult                                  deleteTask(TaskID id);
    TaskModificationResult                                  postponeTask(TaskID id, BoostDate);
    RequestResult                                           complete(TaskID id);

public:
    ~TaskService() override =                               default;

private:
    TaskIDFactory                                           id_generator_;
    std::unique_ptr<TaskStorageInterface>                   storage_;
    std::unique_ptr<PriorityViewInterface<BoostDate>>       by_time_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
    std::unique_ptr<LinkManagerInterface>                   link_manager_;
};


#endif //EVAL_TASKSERVICE_H
