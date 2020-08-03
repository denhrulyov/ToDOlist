//
// Created by denis on 10.07.20.
//

#include "TaskService.h"


TaskDTO getDTO(const std::weak_ptr<TaskNode>& node) {
    auto shared_node = node.lock();
    TaskID id_task = shared_node->getId();
    return TaskDTO(id_task, shared_node->getTask(), shared_node->isComplete());
}

Task getTask(const TaskDTO& task) {
    return Task::create(task.getName(), task.getPriority(), task.getLabel(), task.getDate());
}

Task getPostponedTask(const Task& task, time_t date_postpone) {
    return Task::create(task.getName(), task.getPriority(), task.getLabel(), date_postpone);
}

std::vector<TaskDTO> convertAll(const std::vector<std::weak_ptr<TaskNode>>& all) {
    std::vector<TaskDTO> user_result_set;
    std::transform(all.begin(), all.end(),
                   std::back_inserter(user_result_set),
                   getDTO
    );
    return user_result_set;
}

/**********************************************************************/

void TaskService::addToViews(const std::shared_ptr<TaskNode>& node) {
    by_time_->addToView(node);
    by_label_->addToView(node);
}

void TaskService::eraseFromViews(TaskID id) {
    by_time_->removeFromView(id);
    by_label_->removeFromView(id);
}

TaskCreationResult TaskService::addTask(const TaskDTO &task_data) {
    auto created_node = storage_->createTask(getTask(task_data));
    // set links to new node
    reference_handler_.setReferences(created_node);
    return TaskCreationResult::success(created_node->getId());
}

TaskCreationResult TaskService::addSubTask(TaskID parent, const TaskDTO &task_data) {
    auto parent_node = storage_->getTaskByID(parent);
    if (!parent_node) {
        return TaskCreationResult::taskNotFound();
    }
    auto generated_id = addTask(task_data).getCreatedTaskID().value();
    auto created_node = storage_->getTaskByID(generated_id);
    reference_handler_.linkSubTask(parent_node, created_node);

    return TaskCreationResult::success(generated_id);
}

void TaskService::deleteTask(TaskID id) {
    auto shared_node = storage_->getTaskByID(id);
    for (TaskID subtask : shared_node->getSubtasks()) {
        deleteTask(subtask);
    }
    reference_handler_.removeRefrences(shared_node);
    storage_->eraseTask(id);
}

void TaskService::postponeTask(TaskID id, time_t date_postpone) {
    auto old_node = storage_->getTaskByID(id);
    auto new_node =
            storage_->recreateTask(id, getPostponedTask(old_node->getTask(), date_postpone));

    reference_handler_.moveInternalRefrences(old_node, new_node);
    reference_handler_.removeRefrences(old_node);
    reference_handler_.setReferences(new_node);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    auto result_set = by_time_->getAll(std::numeric_limits<time_t>::max());
    return convertAll(result_set);
}

std::vector<TaskDTO> TaskService::getAllWithLabel(const std::string &label) {
    auto result_set = by_label_->getAll(label);
    return convertAll(result_set);
}


TaskDTO TaskService::getTaskByID(TaskID id) {
    return TaskDTO(id, storage_->getTaskByID(id)->getTask());
}

void TaskService::complete(TaskID id) {
    auto shared_node = storage_->getTaskByID(id);
    shared_node->complete();
    for (TaskID child : shared_node->getSubtasks()) {
        complete(child);
    }
}

