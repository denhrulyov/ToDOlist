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
    return repository_holder_->GetModel().addTask(task_data);
}

TaskCreationResult TaskService::addSubTask(TaskID parent, const TaskDTO &task_data) {
    if (!validate_date(task_data.getDate())) {
        return TaskCreationResult::error("Task date is out of allowed range");
    }
    return repository_holder_->GetModel().addSubTask(parent, task_data);
}

TaskModificationResult
TaskService::deleteTask(TaskID id) {
    return repository_holder_->GetModel().dropTask(id);
}

TaskModificationResult
TaskService::postponeTask(TaskID id, BoostDate date_postpone) {
    std::optional<TaskDTO> is_old_task = repository_holder_->GetModel().getTaskData(id);
    if (!is_old_task) {
        return TaskModificationResult::taskNotFound();
    }
    TaskDTO old_task = is_old_task.value();

    return
    repository_holder_->GetModel().setTaskData(
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
    return repository_holder_->GetModel().getWithLabel(label);
}


std::optional<TaskDTO> TaskService::getTaskByID(TaskID id) {
    return repository_holder_->GetModel().getTaskData(id);
}

RequestResult TaskService::complete(TaskID id) {
    TaskRepositoryInterface& model = repository_holder_->GetModel();
    auto root_complete_result = model.setCompleted(id);
    if (!root_complete_result.getSuccessStatus()) {
        return root_complete_result;
    }
    for (const auto& task : model.getSubTasksRecursive(id)) {
        auto complete_result = model.setCompleted(task.getId());
        if (!complete_result.getSuccessStatus()) {
            return complete_result;
        }
    }
    return RequestResult::success();
}

std::vector<TaskDTO> TaskService::getToday() {
    using namespace boost::gregorian;
    return repository_holder_->GetModel().getToDate(day_clock::local_day());
}

std::vector<TaskDTO> TaskService::getThisWeek() {
    using namespace boost::gregorian;
    return repository_holder_->GetModel().getToDate(day_clock::local_day() + days(6));
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    using namespace boost::gregorian;
    return repository_holder_->GetModel().getToDate(service::max_date);
}

std::vector<TaskDTO> TaskService::getSubTasks(TaskID id) {
    return repository_holder_->GetModel().getSubTasks(id);
}


std::vector<TaskDTO> TaskService::getSubTasksRecursive(TaskID id) {
    return repository_holder_->GetModel().getSubTasksRecursive(id);
}

RequestResult TaskService::saveToFile(const std::string &filepath) {
    bool saved = repository_holder_->SaveModelToFile(filepath);
    return saved ? RequestResult::success() : RequestResult(false, "Could not save");
}

RequestResult TaskService::loadFromFile(const std::string &filepath) {
    bool loaded = repository_holder_->LoadModelFromFile(filepath);
    return loaded ? RequestResult::success() : RequestResult(false, "Could not load");
}

