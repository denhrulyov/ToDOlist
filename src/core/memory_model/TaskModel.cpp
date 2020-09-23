//
// Created by denis on 23.09.20.
//

#include "TaskModel.h"

TaskCreationResult TaskModel::addTask(const TaskDTO &task_data) {
    auto created_node = std::make_shared<TaskNode>(
            id_generator_.generateID(),
            TaskDTOConverter::getTask(task_data)
    );
    TaskStorageInterface::Result result = storage_->addTask(created_node);
    if (result != TaskStorageInterface::Result::SUCCESS) {
        return TaskCreationResult::error("Storage error");
    }
    link_manager_->setLinks(created_node);

    return TaskCreationResult::success(created_node->getId());
}

TaskCreationResult TaskModel::addSubTask(TaskID parent, const TaskDTO &task_data) {
    auto parent_node = storage_->getTaskByID(parent).lock();
    if (!parent_node) {
        return TaskCreationResult::taskNotFound();
    }
    auto add_result = addTask(task_data);
    if (!add_result.getSuccessStatus()) {
        return add_result;
    }
    auto generated_id = add_result.getCreatedTaskID().value();
    auto created_node = storage_->getTaskByID(generated_id).lock();
    link_manager_->linkSubTask(parent_node, created_node);

    return TaskCreationResult::success(generated_id);
}

TaskModificationResult TaskModel::setTaskData(TaskID id, const TaskDTO &new_data) {
    auto old_node = storage_->getTaskByID(id).lock();
    if (!old_node) {
        return TaskModificationResult::taskNotFound();
    }
    auto new_node = old_node->clone(TaskDTOConverter::getTask(new_data));
    link_manager_->moveInboundLinks(old_node, new_node);
    storage_->eraseTask(id);
    storage_->addTask(new_node);
    return TaskModificationResult::success();
}

std::optional<TaskDTO> TaskModel::getTaskData(TaskID id) {
    auto node = storage_->getTaskByID(id).lock();
    return node ? std::make_optional(TaskDTOConverter::getDTO(node)) : std::nullopt;
}

TaskModificationResult TaskModel::dropTask(TaskID id) {
    auto shared_node = storage_->getTaskByID(id).lock();
    if (!shared_node) {
        return TaskModificationResult::taskNotFound();
    }
    for (TaskID subtask : shared_node->getSubtasks()) {
        auto result = dropTask(subtask);
        if (!result.getSuccessStatus()) {
            return result;
        }
    }
    link_manager_->removeLinks(shared_node);
    storage_->eraseTask(id);
    return TaskModificationResult::success();
}

TaskModificationResult TaskModel::setCompleted(TaskID id) {
    auto to_complete = storage_->getTaskByID(id).lock();
    if (!to_complete) {
        return TaskModificationResult::taskNotFound();
    }
    to_complete->complete();
    return TaskModificationResult::success();
}

const PriorityViewInterface<BoostDate>& TaskModel::dateFilter() {
    return *by_date_;
}

const PriorityViewInterface<std::string>& TaskModel::labelFilter() {
    return *by_label_;
}
