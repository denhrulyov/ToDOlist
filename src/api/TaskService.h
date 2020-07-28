//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskFactoryInterface.h"
#include "memory_model/TaskControllerInterface.h"
#include "memory_model/PriorityView.h"
#include "TaskCreationResult.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

class TaskService {

public:
    TaskService(std::unique_ptr<PriorityViewInterface> service,
                std::unique_ptr<TaskControllerInterface> task_tree,
                std::unique_ptr<TaskFactoryInterface> task_creator
                ) :
    task_tree_(std::move(task_tree)),
    by_priority_(std::move(service)),
    task_creator_(std::move(task_creator))
    {}

    std::vector<TaskDTO> getAllTasks();
    TaskDTO getTaskByID(TaskID id_task);

public:
    TaskCreationResult          addTask(const TaskDTO &user_data);
    TaskCreationResult          addSubTask(TaskID id_parent, const TaskDTO &user_data);
    void                        deleteTask(TaskID id_task);
    void                        postponeTask(TaskID id_task, time_t date);

private:
    TaskDTO getTaskBySystemID(TaskID id_task);

    std::unique_ptr<TaskFactoryInterface>         task_creator_;
    std::unique_ptr<TaskControllerInterface>      task_tree_;
    std::unique_ptr<PriorityViewInterface>        by_priority_;
};


#endif //EVAL_TASKSERVICE_H
