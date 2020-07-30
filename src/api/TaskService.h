//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskFactoryInterface.h"
#include "memory_model/TaskControllerInterface.h"
#include "memory_model/DatePriorityView.h"
#include "TaskCreationResult.h"
#include "memory_model/TaskIDFactory.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

class TaskService {

public:
    TaskService(
            std::unique_ptr<TaskIDFactoryInterface>                 id_generator,
            std::unique_ptr<TaskFactoryInterface>                   task_creator,
            std::unique_ptr<PriorityViewInterface<time_t>>          view_time,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label
            ) :
            id_generator_(std::move(id_generator)),
            task_creator_(std::move(task_creator)),
            by_time_(std::move(view_time)),
            by_label_(std::move(view_label))
    {}

public:
    std::vector<TaskDTO>                                    getAllTasks();
    std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label);
    TaskDTO                                                 getTaskByID(TaskID id_task);

public:
    TaskCreationResult                                      addTask(const TaskDTO &user_data);
    TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &user_data);
    void                                                    deleteTask(TaskID id);
    void                                                    postponeTask(TaskID id, time_t date);

private:
    void                                                    addToViews(const std::shared_ptr<TaskNode>&);
    void                                                    eraseAllReferences(TaskID id);

private:
    std::map<TaskID, std::shared_ptr<TaskNode>>             nodes_;
    std::unique_ptr<TaskIDFactoryInterface>                 id_generator_;
    std::unique_ptr<TaskFactoryInterface>                   task_creator_;
    std::unique_ptr<PriorityViewInterface<time_t>>          by_time_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
};


#endif //EVAL_TASKSERVICE_H
