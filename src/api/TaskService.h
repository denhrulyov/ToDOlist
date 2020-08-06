//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskStrorageInterface.h"
#include "TaskCreationResult.h"
#include "memory_model/TaskIDFactory.h"
#include "memory_model/ReferenceHandler.h"
#include "TaskDTOConverter.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

class TaskService {

public:
    TaskService(
            std::unique_ptr<TaskStrorageInterface>                  storage,
            std::unique_ptr<PriorityViewInterface<Gregorian>>       view_time,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label,
            const ReferenceHandler&                                 reference_handler
            ) :
            storage_(std::move(storage)),
            by_time_(std::move(view_time)),
            by_label_(std::move(view_label)),
            reference_handler_(reference_handler)
    {}

public:
    std::vector<TaskDTO>                                    getAllTasks();
    std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label);
    std::optional<TaskDTO>                                  getTaskByID(TaskID id_task);

public:
    TaskCreationResult                                      addTask(const TaskDTO &user_data);
    TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &user_data);
    void                                                    deleteTask(TaskID id);
    void                                                    postponeTask(TaskID id, Gregorian);
    void                                                    complete(TaskID id);

private:
    std::unique_ptr<TaskStrorageInterface>                  storage_;
    std::unique_ptr<PriorityViewInterface<Gregorian>>       by_time_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
    ReferenceHandler                                        reference_handler_;
};


#endif //EVAL_TASKSERVICE_H
