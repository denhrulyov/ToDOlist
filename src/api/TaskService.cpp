//
// Created by denis on 10.07.20.
//

#include "TaskService.h"



Task getPostponedTask(const Task& task, Gregorian date_postpone) {
    return Task::create(task.getName(), task.getPriority(), task.getLabel(), date_postpone);
}

std::vector<TaskDTO> convertAll(const std::vector<std::weak_ptr<TaskNode>>& all) {
    std::vector<TaskDTO> user_result_set;
    std::transform(all.begin(), all.end(),
                   std::back_inserter(user_result_set),
                   [] (std::weak_ptr<TaskNode> node) {
                        return TaskDTOConverter::getDTO(node.lock());
                    }
    );
    return user_result_set;
}

std::shared_ptr<TaskNode> createNode(TaskID id, const Task& task) {
    return std::make_shared<TaskNode>(id, task);
}

/**********************************************************************/

TaskCreationResult TaskService::addTask(const TaskDTO &task_data) {
    auto created_node = createNode(
            id_generator_.generateID(),
            TaskDTOConverter::getTask(task_data)
    );
    TaskStrorageInterface::Result result = storage_->addTask(created_node);
    if (result != TaskStrorageInterface::Result::SUCCESS) {
        return TaskCreationResult::error("Storage error");
    }
    reference_handler_.setReferences(created_node);

    return TaskCreationResult::success(created_node->getId());
}

TaskCreationResult TaskService::addSubTask(TaskID parent, const TaskDTO &task_data) {
    auto parent_node = storage_->getTaskByID(parent).lock();
    if (!parent_node) {
        return TaskCreationResult::taskNotFound();
    }
    auto add_result = addTask(task_data);
    if (add_result.getSuccessStatus() == false) {
        return add_result;
    }
    auto generated_id = add_result.getCreatedTaskID().value();
    auto created_node = storage_->getTaskByID(generated_id).lock();
    reference_handler_.linkSubTask(parent_node, created_node);

    return TaskCreationResult::success(generated_id);
}

TaskModificationResult
TaskService::deleteTask(TaskID id) {
    auto shared_node = storage_->getTaskByID(id).lock();
    if (!shared_node) {
        return TaskModificationResult::taskNotFound();
    }
    for (TaskID subtask : shared_node->getSubtasks()) {
        auto result = deleteTask(subtask);
        if (result.getSuccessStatus() == false) {
            return result;
        }
    }
    reference_handler_.removeRefrences(shared_node);
    storage_->eraseTask(id);
    return TaskModificationResult::success(id);
}

TaskModificationResult
TaskService::postponeTask(TaskID id, Gregorian date_postpone) {
    auto old_node = storage_->getTaskByID(id).lock();
    if (!old_node) {
        return TaskModificationResult::taskNotFound();
    }
    auto new_node = old_node->clone(getPostponedTask(old_node->getTask(), date_postpone));
    reference_handler_.moveInboundRefrences(old_node, new_node);
    reference_handler_.removeRefrences(old_node);
    reference_handler_.setReferences(new_node);
    storage_->eraseTask(id);
    storage_->addTask(new_node);
    return TaskModificationResult::success(id);
}


std::vector<TaskDTO> TaskService::getAllWithLabel(const std::string &label) {
    auto result_set = by_label_->getAllWithConstraint(label);
    return convertAll(result_set);
}


std::optional<TaskDTO> TaskService::getTaskByID(TaskID id) {
    auto node = storage_->getTaskByID(id).lock();
    return node ? std::make_optional(TaskDTOConverter::getDTO(node)) : std::nullopt;
}

RequestResult TaskService::complete(TaskID id) {
    auto shared_node = storage_->getTaskByID(id).lock();
    shared_node->complete();
    for (TaskID child : shared_node->getSubtasks()) {
        complete(child);
    }
    return RequestResult::success();
}

std::vector<TaskDTO> TaskService::getToday() {
    using namespace boost::gregorian;
    auto result_set = by_time_->getAllWithConstraint(day_clock::local_day());
    return convertAll(result_set);
}

std::vector<TaskDTO> TaskService::getThisWeek() {
    using namespace boost::gregorian;
    auto result_set = by_time_->getAllWithConstraint(day_clock::local_day() + days(6));
    return convertAll(result_set);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    using namespace boost::gregorian;
    auto result_set = by_time_->getAllWithConstraint(day_clock::local_day() + years(100));
    return convertAll(result_set);
}

