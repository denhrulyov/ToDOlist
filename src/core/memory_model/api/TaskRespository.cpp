//
// Created by denis on 23.09.20.
//


#include "TaskRespository.h"



std::vector<RepositoryTaskDTO> convertAllNodes(const std::vector<std::weak_ptr<TaskNode>>& all) {
    std::vector<RepositoryTaskDTO> user_result_set;
    std::transform(all.begin(), all.end(),
                   std::back_inserter(user_result_set),
                   [] (std::weak_ptr<TaskNode> node) {
                       return TaskDTOConverter::getDTO(node.lock());
                   }
    );
    return user_result_set;
}

/*****************************************************************************/

TaskCreationResult TaskRespository::addTask(const RepositoryTaskDTO &task_data) {
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

TaskCreationResult TaskRespository::addSubTask(TaskID parent, const RepositoryTaskDTO &task_data) {
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

TaskModificationResult TaskRespository::setTaskData(TaskID id, const RepositoryTaskDTO &new_data) {
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

std::optional<RepositoryTaskDTO> TaskRespository::getTaskData(TaskID id) const {
    auto node = storage_->getTaskByID(id).lock();
    return node ? std::make_optional(TaskDTOConverter::getDTO(node)) : std::nullopt;
}

TaskModificationResult TaskRespository::dropTask(TaskID id) {
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

TaskModificationResult TaskRespository::setCompleted(TaskID id) {
    auto to_complete = storage_->getTaskByID(id).lock();
    if (!to_complete) {
        return TaskModificationResult::taskNotFound();
    }
    to_complete->complete();
    return TaskModificationResult::success();
}

std::vector<RepositoryTaskDTO> TaskRespository::getToDate(const BoostDate &date_to) const {
    return convertAllNodes(by_date_->getAllWithConstraint(date_to));
}

std::vector<RepositoryTaskDTO> TaskRespository::getWithLabel(const std::string &label) const {
    return convertAllNodes(by_label_->getAllWithConstraint(label));
}

std::vector<RepositoryTaskDTO> TaskRespository::getSubTasks(TaskID id) const {
    auto parent = storage_->getTaskByID(id).lock();
    if (parent) {
        return convertAllNodes(parent->getSubNodes());
    }
    return std::vector<RepositoryTaskDTO>{};
}

std::vector<RepositoryTaskDTO> get_children_recurse(const std::shared_ptr<TaskNode>& node) {
    std::vector<RepositoryTaskDTO> result = { TaskDTOConverter::getDTO(node) };
    for (const auto& child : node->getSubNodes()) {
        auto sub_result = get_children_recurse(child.lock());
        result.insert(result.end(), sub_result.begin(), sub_result.end());
    }
    return result;
}

std::vector<RepositoryTaskDTO> TaskRespository::getSubTasksRecursive(TaskID id) const {
    auto parent = storage_->getTaskByID(id).lock();
    if (parent) {
        std::vector<RepositoryTaskDTO> result;
        for (const auto& child : parent->getSubNodes()) {
            auto sub_result = get_children_recurse(child.lock());
            result.insert(result.end(), sub_result.begin(), sub_result.end());
        }
        return result;
    }
    return std::vector<RepositoryTaskDTO>{};
}

std::vector<RepositoryTaskDTO> TaskRespository::getAllTasks() const {
    return convertAllNodes(storage_->getAllTasks());
}

std::optional<RepositoryTaskDTO> TaskRespository::getParentTask(TaskID id) const {
    auto node = storage_->getTaskByID(id).lock();
    if (!node) {
        return std::nullopt;
    }
    auto parent = node->getParent().lock();
    return parent ? getTaskData(parent->getId()) : std::nullopt;
}
