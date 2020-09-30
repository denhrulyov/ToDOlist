//
// Created by denis on 10.07.20.
//

#include "TaskService.h"



bool validate_date(const BoostDate& date) {
    return  date <= service::max_date &&
            date >= boost::gregorian::day_clock::local_day();
}

/**********************************************************************/

TaskCreationResult TaskService::addTask(const TaskDTO &task_data) {
    if (!validate_date(task_data.getDate())) {
        return TaskCreationResult::error("Task date is out of allowed range");
    }
    return model_->addTask(task_data);
}

TaskCreationResult TaskService::addSubTask(TaskID parent, const TaskDTO &task_data) {
    if (!validate_date(task_data.getDate())) {
        return TaskCreationResult::error("Task date is out of allowed range");
    }
    return model_->addSubTask(parent, task_data);
}

TaskModificationResult
TaskService::deleteTask(TaskID id) {
    return model_->dropTask(id);
}

TaskModificationResult
TaskService::postponeTask(TaskID id, BoostDate date_postpone) {
    std::optional<TaskDTO> is_old_task = model_->getTaskData(id);
    if (!is_old_task) {
        return TaskModificationResult::taskNotFound();
    }
    TaskDTO old_task = is_old_task.value();

    return
    model_->setTaskData(
            id,
            TaskDTO::create(
                    id,
                    old_task.getName(),
                    old_task.getPriority(),
                    old_task.getLabel(),
                    date_postpone,
                    old_task.isCompleted()
                    ));
}

std::vector<TaskDTO> TaskService::getAllWithLabel(const std::string &label) {
    return model_->getWithLabel(label);
}


std::optional<TaskDTO> TaskService::getTaskByID(TaskID id) {
    return model_->getTaskData(id);
}

RequestResult TaskService::complete(TaskID id) {
    auto root_complete_result = model_->setCompleted(id);
    if (!root_complete_result.getSuccessStatus()) {
        return root_complete_result;
    }
    for (const auto& task : model_->getSubTasksRecursive(id)) {
        auto complete_result = model_->setCompleted(task.getId());
        if (!complete_result.getSuccessStatus()) {
            return complete_result;
        }
    }
    return RequestResult::success();
}

std::vector<TaskDTO> TaskService::getToday() {
    using namespace boost::gregorian;
    return model_->getToDate(day_clock::local_day());
}

std::vector<TaskDTO> TaskService::getThisWeek() {
    using namespace boost::gregorian;
    return model_->getToDate(day_clock::local_day() + days(6));
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    using namespace boost::gregorian;
    return model_->getToDate(service::max_date);
}

std::vector<TaskDTO> TaskService::getSubTasks(TaskID id) {
    return model_->getSubTasks(id);
}


std::vector<TaskDTO> TaskService::getSubTasksRecursive(TaskID id) {
    return model_->getSubTasksRecursive(id);
}

