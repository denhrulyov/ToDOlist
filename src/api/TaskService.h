//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskFactoryInterface.h"
#include "memory_model/TaskControllerInterface.h"
#include "memory_model/PriorityView.h"
#include "TaskIDConverterInterface.h"
#include <unordered_map>
#include <algorithm>
#include <memory>

class TaskService {

public:
    TaskService(std::unique_ptr<PriorityViewInterface> service,
                std::unique_ptr<TaskControllerInterface> task_tree,
                std::unique_ptr<TaskIDConverterInterface> id_converter,
                std::unique_ptr<TaskFactoryInterface> task_creator
                ) :
    task_tree_(std::move(task_tree)),
    by_priority_(std::move(service)),
    id_converter_(std::move(id_converter)),
    task_creator_(std::move(task_creator))
    {}

    std::vector<TaskDTO> getAllTasks();

public:
    UserTaskID      addTask(const TaskDTO &user_data);
    UserTaskID      addSubTask(const TaskDTO &user_data);
    void            deleteTask(TaskID id_task);

    void inspectRoot() {
        task_tree_->see();
    }
private:
    std::unique_ptr<TaskFactoryInterface>         task_creator_;
    std::unique_ptr<TaskControllerInterface>      task_tree_;
    std::unique_ptr<TaskIDConverterInterface>     id_converter_;
    std::unique_ptr<PriorityViewInterface>        by_priority_;
};


#endif //EVAL_TASKSERVICE_H
